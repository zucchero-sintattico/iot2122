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

// Sensors import
#include "sensor/sugar/SugarManager.h"
#include "sensor/button/ButtonManager.h"

// Utilities import
#include "config/MessageType.h"

// Pin configurations
uint8_t potentiometerPin = A0;
uint8_t buttonUpPin = 2;
uint8_t buttonDownPin = 3;
uint8_t buttonMakePin = 4;

// Sensors configurations
SugarManager* sugarManager = new SugarManager(potentiometerPin);
ButtonManager* buttonUpManager = new ButtonManager(buttonUpPin);
ButtonManager* buttonDownManager = new ButtonManager(buttonDownPin);
ButtonManager* buttonMakeManager = new ButtonManager(buttonMakePin);

const size_t nSensor = 4;
SensorManager* sensorManagers[nSensor] = {
    sugarManager,
    buttonUpManager,
    buttonDownManager,
    buttonMakeManager
};

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
    for (size_t i = 0; i < nSensor; i++)
    {
        SensorManager* sensorManager = sensorManagers[i];
        sensorManager->computeRead();
    }
    scheduler->schedule();
}