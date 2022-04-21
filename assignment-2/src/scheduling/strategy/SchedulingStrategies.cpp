#include "SchedulingStrategies.h"


#include "scheduling/strategy/period-based-scheduling-strategy/PeriodBasedSchedulingStrategy.h"
#include "scheduling/strategy/random-scheduling-strategy/RandomSchedulingStrategy.h"

SchedulingStrategy* SchedulingStrategies::FromPeriod(int period) {
    return new PeriodBasedSchedulingStrategy(period);
}

SchedulingStrategy* SchedulingStrategies::Random() {
    return new RandomSchedulingStrategy();
}