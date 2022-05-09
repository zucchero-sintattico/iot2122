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

// Device configurations
#include "smart-coffee-machine/config/device/Device.h"
#include "smart-coffee-machine/config/device/DeviceBuilder.h"
#define potentiometerPin A0
#define thermometerPin A1
#define buttonMakePin 2
#define buttonUpPin 3
#define buttonDownPin 4
#define sonarEchoPin 5
#define sonarTrigPin 6
#define servoPin 7
#define pirPin 8

Device* device = (new DeviceBuilder())
->withButtonUp(new Button(buttonUpPin))
->withButtonDown(new Button(buttonDownPin))
->withButtonMake(new Button(buttonMakePin))
->withSugar(new Sugar(potentiometerPin))
->withPir(new Pir(pirPin))
->withThermometer(new Thermometer(thermometerPin))
->withSonar(new Sonar(sonarTrigPin, sonarEchoPin))
->withMotor(new Motor(servoPin))
->withCoffeeDisplayI2C(ProxyCoffeeDisplayI2C::getInstance())
->build();

// Application data
AppData* appData = new AppData();

// Scheduler and Tasks configurations
MessageBus<MessageType>* messageBus = new MessageBus<MessageType>();
SchedulerWithMessageBus<MessageType>* scheduler = new SchedulerWithMessageBus<MessageType>(messageBus);

// Utility Task
MemoryCheckTask* memoryCheckTask = new MemoryCheckTask();

// App Tasks
BootTask* bootTask = new BootTask(device);
PresenceTask* presenceTask = new PresenceTask(device);
BeverageSelectorTask* beverageSelectorTask = new BeverageSelectorTask(appData, device);
BeverageMakerTask* beverageMakerTask = new BeverageMakerTask(appData, device);
SelfCheckTask* selfCheckTask = new SelfCheckTask(device);
ApplicationCommunicatorTask* applicationCommunicatorTask = new ApplicationCommunicatorTask(appData);

#define NTASKS 7
CommunicablePeriodBasedTask<MessageType>* tasks[NTASKS] = {
    memoryCheckTask,
    bootTask,
    beverageSelectorTask,
    beverageMakerTask,
    selfCheckTask,
    applicationCommunicatorTask,
    presenceTask
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