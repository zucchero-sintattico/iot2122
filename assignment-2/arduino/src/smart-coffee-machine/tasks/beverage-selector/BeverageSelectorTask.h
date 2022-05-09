#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include "smart-coffee-machine/config/MessageType.h"

// Sensors & Actuator
#include "smart-coffee-machine/config/device/Device.h"

// Data
#include "smart-coffee-machine/config/data/AppData.h"

#include <Arduino.h>

enum class BeverageSelectorTaskState : uint8_t {
    IDLE,
    READY,
    SELECTING,
    ASSISTANCE
};

#define MAX_SELECTING_TIME 5000

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

    private:
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
    BeverageSelectorTask(AppData* appData, Device* device) : CommunicablePeriodBasedTaskWithFSM(BeverageSelectorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
        this->buttonUp = device->getButtonUp();
        this->buttonDown = device->getButtonDown();
        this->buttonMake = device->getButtonMake();
        this->sugarManager = device->getSugar();
        this->display = device->getCoffeeDisplayI2C();
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