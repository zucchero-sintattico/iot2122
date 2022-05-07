#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>

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
    int _period = 1000;

public:

    ApplicationCommunicatorTask() : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
    }

    void init();
    void computeRead();
    void tick();

};

#endif