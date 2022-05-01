#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum class PresenceTaskState {
    IDLE,
    EMPTY,
    SOMEONE,
    SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

    public:
    int period = 500;

    PresenceTask() : CommunicablePeriodBasedTaskWithFSM(PresenceTaskState::IDLE) {}

    void init();
    void computeRead();
    void tick();
};

#endif