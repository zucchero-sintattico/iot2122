#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum PresenceTaskState {
    EMPTY,
    SOMEONE,
    PRE_SLEEP,
    SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

public:
    static const int period = 500;

    PresenceTask(MessageBus<MessageType>* messageBus) : CommunicablePeriodBasedTaskWithFSM(messageBus, PresenceTaskState::EMPTY) {}

    void init();
    void tick();
};

#endif