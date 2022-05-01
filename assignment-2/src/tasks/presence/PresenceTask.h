#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum PresenceTaskState {
    PRESENCE_STATE_IDLE,
    PRESENCE_STATE_EMPTY,
    PRESENCE_STATE_SOMEONE,
    PRESENCE_STATE_SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

    public:
    int period = 500;

    PresenceTask() : CommunicablePeriodBasedTaskWithFSM(PRESENCE_STATE_IDLE) {}

    void init();
    void computeRead();
    void tick();
};

#endif