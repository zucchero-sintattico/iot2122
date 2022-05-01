#ifndef _RANDOM_SCHEDULING_STRATEGY_H_
#define _RANDOM_SCHEDULING_STRATEGY_H_

#include "../SchedulingStrategy.h"

class RandomSchedulingStrategy : public SchedulingStrategy {
    public:
    virtual bool hasToBeExecuted();
};

#endif