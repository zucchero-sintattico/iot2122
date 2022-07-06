#include "SchedulingStrategies.h"

#include "./period-based-scheduling-strategy/PeriodBasedSchedulingStrategy.h"
#include "./random-scheduling-strategy/RandomSchedulingStrategy.h"

SchedulingStrategy* SchedulingStrategies::FromPeriod(int period) {
    return new PeriodBasedSchedulingStrategy(period);
}

SchedulingStrategy* SchedulingStrategies::Random() {
    return new RandomSchedulingStrategy();
}