#ifndef _PERIOD_BASED_SCHEDULING_STRATEGY_H_
#define _PERIOD_BASED_SCHEDULING_STRATEGY_H_

#include "scheduling/strategy/SchedulingStrategy.h"

class PeriodBasedSchedulingStrategy : public SchedulingStrategy {

    int period;

public:
    PeriodBasedSchedulingStrategy(int period);
    virtual bool hasToBeExecuted();

};

#endif