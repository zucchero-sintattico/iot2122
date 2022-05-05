#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/MessageType.h"
#include "smart-coffee-machine/sensors/button/ButtonManager.h"
#include "smart-coffee-machine/sensors/sugar/SugarManager.h"
#include "smart-coffee-machine/config/data/AppData.h"

enum class BeverageSelectorTaskState {
    IDLE,
    READY,
    SELECTING,
    ASSISTANCE
};

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

private:
    int _period = 50;

    // Configuration
    int buttonUpPin;
    int buttonDownPin;
    int buttonMakePin;
    int potentiometerSugarPin;

    ButtonManager* buttonUpManager;
    ButtonManager* buttonDownManager;
    ButtonManager* buttonMakeManager;
    SugarManager* sugarManager;

    AppData* appData;

public:
    BeverageSelectorTask(AppData* appData, int buttonUpPin, int buttonDownPin, int buttonMakePin, int potentiometerSugarPin) : CommunicablePeriodBasedTaskWithFSM(BeverageSelectorTaskState::IDLE) {
        this->setPeriod(50);
        this->appData = appData;

        this->buttonUpPin = buttonUpPin;
        this->buttonDownPin = buttonDownPin;
        this->buttonMakePin = buttonMakePin;
        this->potentiometerSugarPin = potentiometerSugarPin;

        this->buttonUpManager = new ButtonManager(buttonUpPin);
        this->buttonDownManager = new ButtonManager(buttonDownPin);
        this->buttonMakeManager = new ButtonManager(buttonMakePin);
        this->sugarManager = new SugarManager(potentiometerSugarPin);
    }

    void init();
    void computeRead();
    void tick();

private:
    void onIdleState();
    void onReadyState();
    void onSelectingState();
    void onAssistanceState();

    bool isAnyButtonPressed();

};

#endif