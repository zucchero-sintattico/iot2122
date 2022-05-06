#ifndef _PERIOD_BASED_TASK_H_
#define _PERIOD_BASED_TASK_H_

#include "Task.h"

class PeriodBasedTask : public Task {

private:
    int period;
public:
    void setPeriod(int period) {
        this->period = period;
    }
    int getPeriod() {
        return this->period;
    }

};

#endif