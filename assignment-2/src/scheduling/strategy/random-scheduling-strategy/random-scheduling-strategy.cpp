#include "random-scheduling-strategy.h"

bool RandomSchedulingStrategy::hasToBeExecuted() {
    return rand() > (RAND_MAX / 2);
}