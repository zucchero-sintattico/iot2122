#include <Arduino.h>

#include "scheduling/scheduler/scheduler.h"
#include "scheduling/task/task.h"

#include "tasks/blink-task/blink-task.h"
#include "scheduling/strategy/period-based-scheduling-strategy/period-based-scheduling-strategy.h"


Scheduler* scheduler = new Scheduler();
Task* blinkTask = new BlinkTask();

void setup() {

    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(100);

    // Tasks initialization
    blinkTask->setSchedulingStrategy(new PeriodBasedSchedulingStrategy(200));
    blinkTask->init();

    // Add tasks to scheduler
    scheduler->addTask(blinkTask);

}

void loop() {
    scheduler->schedule();
}