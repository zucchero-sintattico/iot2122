
#ifndef _TASK_WITH_SCHEDULING_STRATEGY_H_
#define _TASK_WITH_SCHEDULING_STRATEGY_H_


#include "utils/pair/pair.h"
#include "scheduling/task/task.h"
#include "scheduling/strategy/scheduling-strategy.h"

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