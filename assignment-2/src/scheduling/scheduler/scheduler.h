#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "utils/pair/pair.h"
#include "task-with-scheduling-strategy/task-with-scheduling-strategy.h"
#include "scheduling/timer/timer.h"
#include "scheduling/strategy/scheduling-strategy.h"
#include "scheduling/task/task.h"


/**
 * @brief A scheduler is a class that manages the execution of tasks.
 */
class Scheduler {

    static const int MAX_TASKS = 10;

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