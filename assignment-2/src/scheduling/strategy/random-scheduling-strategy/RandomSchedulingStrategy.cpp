#include "RandomSchedulingStrategy.h"

bool RandomSchedulingStrategy::hasToBeExecuted() {
    return rand() > (RAND_MAX / 2);
}