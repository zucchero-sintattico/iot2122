#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#include "./task-with-scheduling-strategy/TaskWithSchedulingStrategy.h"
#include "../timer/Timer.h"
#include "../strategy/SchedulingStrategy.h"
#include "../task/Task.h"
#include "../task/PeriodBasedTask.h"
#include <Arduino.h>

/**
 * @brief A scheduler is a class that manages the execution of tasks.
 */
class Scheduler {

    private:
    static const int MAX_TASKS = 10;

    int period;
    uint8_t nTasks;
    TaskWithSchedulingStrategy* tasks[MAX_TASKS];
    Timer timer;

    long previousMillis = 0;

    public:

    void init(int period);
    virtual bool addTask(Task* task, SchedulingStrategy* schedulingStrategy);
    virtual bool addPeriodBasedTask(PeriodBasedTask* task);
    void schedule();

};

#endif