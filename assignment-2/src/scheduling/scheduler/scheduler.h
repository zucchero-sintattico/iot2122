#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "scheduling/timer/timer.h"
#include "scheduling/strategy/scheduling-strategy.h"
#include "scheduling/task/task.h"

#define MAX_TASKS 10

template <class L, class R>
class Pair {
public:
    L* left;
    R* right;

    Pair(L* l, R* r) : left(l), right(r) {}
};

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


class Scheduler {

    int period;
    int nTasks;

    TaskWithSchedulingStrategy* tasks[MAX_TASKS];
    Timer timer;

public:

    virtual void init(int period);
    virtual bool addTask(Task* task, SchedulingStrategy* schedulingStrategy);
    virtual void schedule();

};

#endif