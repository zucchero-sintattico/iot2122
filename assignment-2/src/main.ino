#include <Arduino.h>

// Scheduling import
#include "scheduling/scheduler/Scheduler.h"
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

Scheduler* scheduler = new Scheduler();
MessageBus<MessageType>* messageBus = new MessageBus<MessageType>();

const size_t nTasks = 5;
CommunicablePeriodBasedTask<MessageType>* tasks[nTasks] = {
    new PresenceTask(messageBus),
    new SelfCheckTask(messageBus),
    new ApplicationCommunicatorTask(messageBus),
    new BeverageSelectorTask(messageBus),
    new BeverageMakerTask(messageBus)
};


void setup() {

    // Setup serial
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    // Tasks initialization
    for (size_t i = 0; i < nTasks; i++)
    {
        PeriodBasedTask* task = tasks[i];
        task->init();
        scheduler->addPeriodBasedTask(task);
    }

}

void loop() {
    scheduler->schedule();
}