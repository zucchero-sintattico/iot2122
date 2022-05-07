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
    FIX,
    REFILL
};

// App -> Arduino
#define REFILL_MESSAGE "REFILL"
#define RECOVER_MESSAGE "RECOVER"

// Arduino -> App
#define IDLE_MESSAGE "IDLE"
#define WORKING_MESSAGE "WORKING"
#define ASSISTANCE_MESSAGE "ASSISTANCE"
#define INFO(COFFEE, TEA, CHOCOLATE) "INFO:" + String(COFFEE) + "," + String(TEA) + "," + String(CHOCOLATE)

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

private:
    int _period = 100;
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
    void onFixState();
    void onRefillState();
};

#endif