#include "scheduling-strategies.h"


#include "scheduling/strategy/period-based-scheduling-strategy/period-based-scheduling-strategy.h"
#include "scheduling/strategy/random-scheduling-strategy/random-scheduling-strategy.h"

SchedulingStrategy* SchedulingStrategies::FromPeriod(int period) {
    return new PeriodBasedSchedulingStrategy(period);
}

SchedulingStrategy* SchedulingStrategies::Random() {
    return new RandomSchedulingStrategy();
}