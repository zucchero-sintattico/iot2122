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
#include "smart-coffee-machine/config/device/Device.h"
#include "smart-coffee-machine/config/device/DeviceBuilder.h"

#include "smart-coffee-machine/actuators/fake-coffee-display-i2c/FakeCoffeeDisplayI2C.h"

// Device configurations
#define potentiometerPin A0
#define thermometerPin A1
#define buttonMakePin 3
#define buttonUpPin 4
#define buttonDownPin 2
#define sonarEchoPin 7
#define sonarTrigPin 8
#define servoPin 9
#define pirPin 5

DeviceBuilder* builder = new DeviceBuilder();
Device* device = builder
->withButtonUp(new Button(buttonUpPin))
->withButtonDown(new Button(buttonDownPin))
->withButtonMake(new Button(buttonMakePin))
->withPotentiometer(new Potentiometer(potentiometerPin))
->withPir(new Pir(pirPin))
->withThermometer(new Thermometer(thermometerPin))
->withSonar(new Sonar(sonarTrigPin, sonarEchoPin))
->withMotor(new Motor(servoPin))
->withCoffeeDisplayI2C(new ProxyCoffeeDisplayI2C())
->build();

// Application data
AppData* appData = new AppData();

// Scheduler and Tasks configurations
SchedulerWithMessageBus<MessageType>* scheduler = new SchedulerWithMessageBus<MessageType>();

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
    scheduler->init(25);
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