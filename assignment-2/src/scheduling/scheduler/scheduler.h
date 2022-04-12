#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "timer/timer.h"
#include "scheduling/task/task.h"

#define MAX_TASKS 10

class Scheduler {

    int period;
    int nTasks;

    Task* taskList[MAX_TASKS];
    Timer timer;

    public:

    virtual void init(int period);
    virtual bool addTask(Task* task);
    virtual void schedule();

};

#endif