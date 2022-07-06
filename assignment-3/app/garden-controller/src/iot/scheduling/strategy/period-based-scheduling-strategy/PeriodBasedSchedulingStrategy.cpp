#include "PeriodBasedSchedulingStrategy.h"

#include <Arduino.h>

PeriodBasedSchedulingStrategy::PeriodBasedSchedulingStrategy(int period) {
    this->period = period;
}

bool PeriodBasedSchedulingStrategy::hasToBeExecuted() {
    return this->elapsedTime >= this->period;
}