#include <Arduino.h>

// Scheduling import
#include "iot/scheduling/scheduler/SchedulerWithMessageBus.h"

// Tasks import
#include "smart-coffee-machine/tasks/memory-check/MemoryCheckTask.h"
#include "smart-coffee-machine/tasks/boot/BootTask.h"
#include "smart-coffee-machine/tasks/presence/PresenceTask.h"
#include "smart-coffee-machine/tasks/self-check/SelfCheckTask.h"
#include "smart-coffee-machine/tasks/application-communicator/ApplicationCommunicatorTask.h"
#include "smart-coffee-machine/tasks/beverage-selector/BeverageSelectorTask.h"
#include "smart-coffee-machine/tasks/beverage-maker/BeverageMakerTask.h"

// Configurations import
#include "smart-coffee-machine/config/data/AppData.h"
#include "smart-coffee-machine/config/MessageType.h"

// Pin configurations
#define potentiometerPin A0
#define thermometerPin A1
#define buttonMakePin 2
#define buttonUpPin 3
#define buttonDownPin 4
#define sonarEchoPin 5
#define sonarTrigPin 6
#define servoPin 7

// Application data
AppData* appData = new AppData();

// Scheduler and Tasks configurations
MessageBus<MessageType>* messageBus = new MessageBus<MessageType>();
SchedulerWithMessageBus<MessageType>* scheduler = new SchedulerWithMessageBus<MessageType>(messageBus);

#define NTASKS 5

MemoryCheckTask* memoryCheckTask = new MemoryCheckTask();
BootTask* bootTask = new BootTask();
BeverageSelectorTask* beverageSelectorTask = new BeverageSelectorTask(appData, buttonUpPin, buttonDownPin, buttonMakePin, potentiometerPin);
BeverageMakerTask* beverageMakerTask = new BeverageMakerTask(appData, sonarTrigPin, sonarEchoPin, servoPin);
SelfCheckTask* selfCheckTask = new SelfCheckTask(servoPin, thermometerPin);

CommunicablePeriodBasedTask<MessageType>* tasks[NTASKS] = {
    memoryCheckTask,
    bootTask,
    beverageSelectorTask,
    beverageMakerTask,
    selfCheckTask
    // new PresenceTask(),
    // new SelfCheckTask(),
    // new ApplicationCommunicatorTask()
};

void setup() {
    Serial.begin(9600);

    // Scheduler initialization
    scheduler->init(50);

    // Tasks initialization
    for (uint8_t i = 0; i < NTASKS; i++)
    {
        CommunicablePeriodBasedTask<MessageType>* task = tasks[i];
        task->init();
        scheduler->addPeriodBasedTask(task);
    }
}

void loop() {
    scheduler->schedule();
}