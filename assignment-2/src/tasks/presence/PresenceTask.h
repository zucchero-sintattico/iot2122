#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "../PeriodBasedTaskWithFSM.h"

enum PresenceTaskState {
    EMPTY,
    SOMEONE,
    PRE_SLEEP,
    SLEEP
};

class PresenceTask : public PeriodBasedTaskWithFSM<PresenceTaskState> {

public:
    static const int period = 500;

    PresenceTask() : PeriodBasedTaskWithFSM(PresenceTaskState::EMPTY) {}

    void init();
    void tick();
};

#endif