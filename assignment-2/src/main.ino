#include <Arduino.h>

#include "scheduling/scheduler/Scheduler.h"
#include "scheduling/task/Task.h"
#include "tasks/blink-task/BlinkTask.h"
#include "scheduling/strategy/SchedulingStrategies.h"


#include "utils/sequence/Sequence.h"

Scheduler* scheduler = new Scheduler();
TaskWithSchedulingStrategy tasks[] = {
        TaskWithSchedulingStrategy(new BlinkTask(), SchedulingStrategies::FromPeriod(500))
};

void setup() {


    auto* tasksSequence = Sequence<TaskWithSchedulingStrategy>::of(tasks, 1);

    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    // Tasks initialization
    tasksSequence->foreach([](TaskWithSchedulingStrategy task) {
        task.getTask()->init();
        scheduler->addTask(task.getTask(), task.getStrategy());
        });
}

void loop() {
    scheduler->schedule();
}