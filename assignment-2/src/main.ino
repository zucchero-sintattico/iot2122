#include <Arduino.h>

#include "scheduling/scheduler/Scheduler.h"
#include "scheduling/task/Task.h"

#include "tasks/blink-task/BlinkTask.h"
#include "scheduling/strategy/SchedulingStrategies.h"
#include "utils/jstream/JStream.h"

Scheduler *scheduler = new Scheduler();
TaskWithSchedulingStrategy tasks[] = {
        TaskWithSchedulingStrategy(new BlinkTask(), SchedulingStrategies::FromPeriod(500))
};

void setup() {
    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    JStream<TaskWithSchedulingStrategy> *taskStream = JStream<TaskWithSchedulingStrategy>::of(tasks, 1);

    // Tasks initialization
    taskStream->foreach([](TaskWithSchedulingStrategy task) {
        task.getTask()->init();
    });

    // Add tasks to scheduler
    taskStream->foreach([](TaskWithSchedulingStrategy task) {
        scheduler->addTask(task.getTask(), task.getStrategy());
    });


    int elems[] = {1, 2, 3};
    JStream<int>::of(elems, 3)
            ->map<int>([](int elem) {
                return elem * 2;
            })
            ->filter([](int elem) {
                return elem >= 4;
            })
            ->foreach([](int elem) {
                Serial.println(elem);
            });
}

void loop() {
    scheduler->schedule();
}