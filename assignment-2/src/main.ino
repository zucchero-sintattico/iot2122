#include <Arduino.h>

// Scheduling import
#include "iot/scheduling/scheduler/SchedulerWithMessageBus.h"

// Tasks import
#include "smart-coffee-machine/tasks/presence/PresenceTask.h"
#include "smart-coffee-machine/tasks/self-check/SelfCheckTask.h"
#include "smart-coffee-machine/tasks/application-communicator/ApplicationCommunicatorTask.h"
#include "smart-coffee-machine/tasks/beverage-selector/BeverageSelectorTask.h"
#include "smart-coffee-machine/tasks/beverage-maker/BeverageMakerTask.h"

// Configurations import
#include "smart-coffee-machine/config/MessageType.h"

// Pin configurations
const uint8_t potentiometerPin = A0;
const uint8_t buttonUpPin = 2;
const uint8_t buttonDownPin = 3;
const uint8_t buttonMakePin = 4;

// Scheduler and Tasks configurations
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