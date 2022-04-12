#ifndef _TASK_H_
#define _TASK_H_

#include "scheduling/strategy/scheduling-strategy.h"

class Task {

    public:
    SchedulingStrategy* schedulingStrategy;

    void setSchedulingStrategy(SchedulingStrategy* schedulingStrategy) {
        this->schedulingStrategy = schedulingStrategy;
    }

    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif