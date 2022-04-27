#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "../PeriodBasedTaskWithFSM.h"

enum SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};

class SelfCheckTask : public PeriodBasedTaskWithFSM<SelfCheckTaskState> {

public:
    static const int period = 50;
    SelfCheckTask() : PeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {}

    void init();
    void tick();

};

#endif