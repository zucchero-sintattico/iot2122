
#ifndef _TASK_WITH_SCHEDULING_STRATEGY_H_
#define _TASK_WITH_SCHEDULING_STRATEGY_H_


#include "utils/pair/Pair.h"
#include "scheduling/task/Task.h"
#include "scheduling/strategy/SchedulingStrategy.h"

class TaskWithSchedulingStrategy : public Pair<Task, SchedulingStrategy> {
public:
    TaskWithSchedulingStrategy(Task* t, SchedulingStrategy* s) : Pair<Task, SchedulingStrategy>(t, s) {}

    Task* getTask() {
        return left;
    }

    SchedulingStrategy* getStrategy() {
        return right;
    }
};

#endif