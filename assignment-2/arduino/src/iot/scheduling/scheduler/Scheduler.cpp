#include "Scheduler.h"

#include "../strategy/SchedulingStrategies.h"

void Scheduler::init(int period) {
    this->period = period;
    timer.setupPeriod(period);
    nTasks = 0;
}

bool Scheduler::addTask(Task* task, SchedulingStrategy* schedulingStrategy) {
    if (nTasks < MAX_TASKS - 1) {
        this->tasks[nTasks] = new TaskWithSchedulingStrategy(task, schedulingStrategy);
        nTasks++;
        return true;
    }
    else {
        return false;
    }
}

bool Scheduler::addPeriodBasedTask(PeriodBasedTask* task) {
    return this->addTask(task, SchedulingStrategies::FromPeriod(task->getPeriod()));
}

void Scheduler::schedule() {
    this->timer.waitForNextTick();
    for (int i = 0; i < nTasks; i++) {
        this->tasks[i]->getStrategy()->addElapsedTime(this->period);
        if (this->tasks[i]->getStrategy()->hasToBeExecuted()) {
            this->tasks[i]->getStrategy()->resetElapsedTime();
            this->tasks[i]->getTask()->computeRead();
            this->tasks[i]->getTask()->tick();
        }
    }
}