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
#include "smart-coffee-machine/config/data/AppData.h"
#include "smart-coffee-machine/config/MessageType.h"

// Pin configurations
const uint8_t potentiometerPin = A0;
const uint8_t buttonMakePin = 2;
const uint8_t buttonUpPin = 3;
const uint8_t buttonDownPin = 4;
const uint8_t sonarEchoPin = 5;
const uint8_t sonarTrigPin = 6;
const uint8_t servoPin = 7;

// Application data
AppData* appData = new AppData();

// Scheduler and Tasks configurations
MessageBus<MessageType>* messageBus = new MessageBus<MessageType>();
SchedulerWithMessageBus<MessageType>* scheduler = new SchedulerWithMessageBus<MessageType>(messageBus);

static const size_t nTasks = 3;
BeverageSelectorTask* beverageSelectorTask = new BeverageSelectorTask(appData, buttonUpPin, buttonDownPin, buttonMakePin, potentiometerPin);
BeverageMakerTask* beverageMakerTask = new BeverageMakerTask(appData, sonarTrigPin, sonarEchoPin, servoPin);
CommunicablePeriodBasedTask<MessageType>* tasks[nTasks] = {
    beverageSelectorTask,
    beverageMakerTask,
    // new PresenceTask(),
    // new SelfCheckTask(),
    new ApplicationCommunicatorTask()
};

void setup() {

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

    messageBus->push(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK);
}

void loop() {
    scheduler->schedule();
}