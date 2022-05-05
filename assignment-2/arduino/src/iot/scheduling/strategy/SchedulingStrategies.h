#ifndef _SCHEDULING_STRATEGIES_H_
#define _SCHEDULING_STRATEGIES_H_


#include "./SchedulingStrategy.h"

class SchedulingStrategies {
    public:
    static SchedulingStrategy* FromPeriod(int period);
    static SchedulingStrategy* Random();
};

#endif