#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "scheduling/task/PeriodBasedTask.h"

class PresenceTask : public PeriodBasedTask {

    public:
    static const int period = 10000;

    void init();
    void tick();
};

#endif