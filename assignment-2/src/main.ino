#include <Arduino.h>

// Scheduling import
#include "scheduling/scheduler/SchedulerWithMessageBus.h"
#include "scheduling/strategy/SchedulingStrategies.h"

// Tasks import
#include "tasks/presence/PresenceTask.h"
#include "tasks/self-check/SelfCheckTask.h"
#include "tasks/application-communicator/ApplicationCommunicatorTask.h"
#include "tasks/beverage-selector/BeverageSelectorTask.h"
#include "tasks/beverage-maker/BeverageMakerTask.h"

// Utilities import
#include "communication/MessageBus.h"
#include "config/MessageType.h"

SchedulerWithMessageBus<MessageType>* scheduler = new SchedulerWithMessageBus<MessageType>();

const size_t nTasks = 5;
CommunicablePeriodBasedTask<MessageType>* tasks[nTasks] = {
    new PresenceTask(),
    new SelfCheckTask(),
    new ApplicationCommunicatorTask(),
    new BeverageSelectorTask(),
    new BeverageMakerTask()
};


void setup() {

    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    // Tasks initialization
    for (size_t i = 0; i < nTasks; i++)
    {
        CommunicablePeriodBasedTask<MessageType>* task = tasks[i];
        task->init();
        scheduler->addPeriodBasedTask(task);
    }
}

void loop() {
    scheduler->schedule();
}