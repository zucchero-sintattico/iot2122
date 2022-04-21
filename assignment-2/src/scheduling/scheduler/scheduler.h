#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "utils/pair/Pair.h"
#include "scheduling/scheduler/task-with-scheduling-strategy/TaskWithSchedulingStrategy.h"
#include "scheduling/timer/Timer.h"
#include "scheduling/strategy/SchedulingStrategy.h"
#include "scheduling/task/Task.h"


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