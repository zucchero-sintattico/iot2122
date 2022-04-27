#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "scheduling/task/PeriodBasedTask.h"

class SelfCheckTask : public PeriodBasedTask {

    public:
    static const int period = 50;

    void init();
    void tick();

};

#endif