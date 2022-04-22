#include <Arduino.h>

#include "scheduling/scheduler/Scheduler.h"
#include "scheduling/task/Task.h"

#include "tasks/blink-task/BlinkTask.h"
#include "scheduling/strategy/SchedulingStrategies.h"
#include "utils/sequence/Sequence.h"

Scheduler *scheduler = new Scheduler();
TaskWithSchedulingStrategy tasks[] = {
        TaskWithSchedulingStrategy(new BlinkTask(), SchedulingStrategies::FromPeriod(500))
};

void setup() {
    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    Sequence<TaskWithSchedulingStrategy> *tasksSequence = Sequence<TaskWithSchedulingStrategy>::of(tasks, 1);

    // Tasks initialization
    tasksSequence->foreach([](TaskWithSchedulingStrategy task) {
        task.getTask()->init();
    });

    // Add tasks to scheduler
    tasksSequence->foreach([](TaskWithSchedulingStrategy task) {
        scheduler->addTask(task.getTask(), task.getStrategy());
    });

    FunctionalPredicate<int> isEven = [](int elem) { return elem % 2 == 0; };

    Predicate<int> evenPredicate = Predicate<int>(isEven);
    Predicate<int> oddPredicate = evenPredicate.negate();
    Predicate<int> oddOrEvenPredicate = evenPredicate.Or(oddPredicate);
    Predicate<int> oddAndEvenPredicate = evenPredicate.And(oddPredicate);
}

void loop() {
    scheduler->schedule();
}