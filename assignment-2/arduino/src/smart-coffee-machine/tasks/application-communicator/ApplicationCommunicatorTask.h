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