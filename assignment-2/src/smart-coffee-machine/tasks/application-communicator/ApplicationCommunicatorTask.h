#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum ApplicationCommunicatorTaskState {
    APPLICATION_COMMUNICATOR_STATE_IDLE,
    APPLICATION_COMMUNICATOR_STATE_SENDING,
    APPLICATION_COMMUNICATOR_STATE_FIX,
    APPLICATION_COMMUNICATOR_STATE_REFILL
};

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

    public:
    int period = 50;

    ApplicationCommunicatorTask() : CommunicablePeriodBasedTaskWithFSM(APPLICATION_COMMUNICATOR_STATE_IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif