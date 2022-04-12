#include <Arduino.h>

#include "scheduling/scheduler/scheduler.h"
#include "scheduling/task/task.h"

#include "tasks/blink-task/blink-task.h"
#include "scheduling/strategy/scheduling-strategies.h"


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