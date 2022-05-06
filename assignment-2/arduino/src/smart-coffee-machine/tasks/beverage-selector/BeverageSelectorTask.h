#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include "smart-coffee-machine/config/MessageType.h"

// Sensors
#include "iot/sensor/button/Button.h"
#include "smart-coffee-machine/sensors/sugar/Sugar.h"

// Actuators
#include "smart-coffee-machine/actuators/proxy-coffee-display-i2c/ProxyCoffeeDisplayI2C.h"
#include "smart-coffee-machine/actuators/fake-coffee-display-i2c/FakeCoffeeDisplayI2C.h"

// Data
#include "smart-coffee-machine/config/data/AppData.h"

enum class BeverageSelectorTaskState {
    IDLE,
    READY,
    SELECTING,
    ASSISTANCE
};

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

private:
    static const unsigned long MAX_SELECTING_TIME = 5000;
    int _period = 50;

    // Sensors
    Button* buttonUp;
    Button* buttonDown;
    Button* buttonMake;
    Sugar* sugarManager;

    // Actuators
    CoffeeDisplayI2C* display;

    AppData* appData;

    long lastIteractionTime;


public:
    BeverageSelectorTask(AppData* appData, int buttonUpPin, int buttonDownPin, int buttonMakePin, int potentiometerSugarPin) : CommunicablePeriodBasedTaskWithFSM(BeverageSelectorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
        this->buttonUp = new Button(buttonUpPin);
        this->buttonDown = new Button(buttonDownPin);
        this->buttonMake = new Button(buttonMakePin);
        this->sugarManager = new Sugar(potentiometerSugarPin);
        this->display = FakeCoffeeDisplayI2C::getInstance();
    }

    // Inherited from task
    void init();
    void computeRead();
    void tick();

private:

    void onIdleState();
    void onReadyState();
    void onSelectingState();
    void onAssistanceState();

    /**
     * @brief Check if any button has been pressed.
     *
     * @return true if any button has been pressed, false otherwise.
     */
    bool isAnyButtonPressed();

    /**
     * @brief Check if the time elapsed since the last iteraction is greater than the max selecting time.
     * @return true if the time is elapsed, false otherwise.
     */
    bool isSelectingTimeElapsed();

};

#endif