#include <Arduino.h>

#include "scheduling/scheduler/Scheduler.h"
#include "scheduling/task/Task.h"

#include "tasks/blink-task/BlinkTask.h"
#include "scheduling/strategy/SchedulingStrategies.h"


Scheduler* scheduler = new Scheduler();
Task* blinkTask = new BlinkTask();

void setup() {

    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    // Tasks initialization
    blinkTask->init();

    // Add tasks to scheduler
    scheduler->addTask(blinkTask, SchedulingStrategies::FromPeriod(100));

}

void loop() {
    scheduler->schedule();
}