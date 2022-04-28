#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum ApplicationCommunicatorTaskState {
    IDLE,
    SENDING,
    FIX,
    REFILL
};

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

public:
    static const int period = 50;

    ApplicationCommunicatorTask(MessageBus<MessageType>* messageBus) : CommunicablePeriodBasedTaskWithFSM(messageBus, ApplicationCommunicatorTaskState::IDLE) {}

    void init();
    void tick();

};

#endif