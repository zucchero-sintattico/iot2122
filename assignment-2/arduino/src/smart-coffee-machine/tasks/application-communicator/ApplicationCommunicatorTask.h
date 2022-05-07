#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>
#include "iot/utils/serial/MsgService.h"
#include "smart-coffee-machine/config/data/AppData.h"

enum class ApplicationCommunicatorTaskState : uint8_t {
    IDLE,
    SENDING,
    RECOVER,
    REFILL
};

// App -> Arduino
#define REFILL_MESSAGE String("REFILL")
#define RECOVER_MESSAGE String("RECOVER")

// Arduino -> App
#define MODALITY String("MODALITY:")
#define IDLE_MESSAGE MODALITY + String("IDLE")
#define WORKING_MESSAGE MODALITY + String("WORKING")
#define ASSISTANCE_MESSAGE MODALITY + String("ASSISTANCE")
#define INFO(COFFEE, TEA, CHOCOLATE) "INFO:" + String(COFFEE) + "," + String(TEA) + "," + String(CHOCOLATE)
#define SELFCHECK(COUNT) "SELFCHECK:" + String(COUNT)

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

private:
    int _period = 1000;
    AppData* appData;
    String commandToExecute;

public:

    ApplicationCommunicatorTask(AppData* appdata) : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appdata;
    }

    void init();
    void computeRead();
    void tick();

    void onIdleState();
    void onSendingState();
    void onRecoverState();
    void onRefillState();
};

#endif