#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum class ApplicationCommunicatorTaskState {
    IDLE,
    SENDING,
    FIX,
    REFILL
};

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

private:
    int _period = 75;

public:

    ApplicationCommunicatorTask() : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        this->setPeriod(this->_period);
    }

    void init();
    void computeRead();
    void tick();

};

#endif