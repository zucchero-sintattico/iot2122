#ifndef _PERIOD_BASED_TASK_H_
#define _PERIOD_BASED_TASK_H_

#include "Task.h"

class PeriodBasedTask : public Task {

public:
    static const int period;
    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif