#include "scheduler.h"
#include <Arduino.h>

void Scheduler::init(int period) {
    this->period = period;
    timer.setupPeriod(period);
    nTasks = 0;
}

bool Scheduler::addTask(Task* task) {
    if (nTasks < MAX_TASKS - 1) {
        taskList[nTasks] = task;
        nTasks++;
        return true;
    }
    else {
        return false;
    }
}

void Scheduler::schedule() {
    timer.waitForNextTick();
    for (int i = 0; i < nTasks; i++) {
        taskList[i]->schedulingStrategy->addElapsedTime(this->period);
        if (taskList[i]->schedulingStrategy->hasToBeExecuted()) {
            taskList[i]->schedulingStrategy->resetElapsedTime();
            taskList[i]->tick();
        }
    }
}