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

private:
    int _period = 500;

public:
    PresenceTask() : CommunicablePeriodBasedTaskWithFSM(PresenceTaskState::IDLE) {
        this->setPeriod(this->_period);
    }

    void init();
    void computeRead();
    void tick();
};

#endif