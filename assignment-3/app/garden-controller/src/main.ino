#include <Arduino.h>

// Scheduling import
#include "iot/scheduling/scheduler/SchedulerWithMessageBus.h"

// Tasks import
#include "garden-controller/tasks/lights-controller/LightsControllerTask.h"
#include "garden-controller/tasks/irrigation-controller/IrrigationControllerTask.h"
#include "garden-controller/tasks/service-communicator/ServiceCommunicatorTask.h"
#include "garden-controller/tasks/application-communicator/ApplicationCommunicatorTask.h"

// Configurations import
#include "garden-controller/config/data/AppData.h"
#include "garden-controller/config/MessageType.h"
#include "garden-controller/config/device/Device.h"
#include "garden-controller/config/device/DeviceBuilder.h"


// Device configurations
#define digitalLed1Pin 3
#define digitalLed2Pin 4
#define analogLed1Pin 5
#define analogLed2Pin 6
#define bluetoothTxPin 7
#define bluetoothRxPin 8
#define servoPin 9

DeviceBuilder* builder = new DeviceBuilder();
Device* device = builder
->withMotor(new Motor(servoPin))
->withDigitalLed1(new DigitalLed(digitalLed1Pin))
->withDigitalLed2(new DigitalLed(digitalLed2Pin))
->withAnalogLed1(new AnalogLed(analogLed1Pin))
->withAnalogLed2(new AnalogLed(analogLed2Pin))
->build();

// Application data
AppData* appData = new AppData();

// Scheduler and Tasks configurations
Scheduler* scheduler = new Scheduler();

// App Tasks
LightsControllerTask* lightsControllerTask = new LightsControllerTask(appData, device);
IrrigationControllerTask* irrigationControllerTask = new IrrigationControllerTask(appData, device);
ServiceCommunicatorTask* serviceCommunicatorTask = new ServiceCommunicatorTask(appData);
ApplicationCommunicatorTask* applicationCommunicatorTask = new ApplicationCommunicatorTask(appData, bluetoothRxPin, bluetoothTxPin);


#define N_TASKS 4
CommunicablePeriodBasedTask<MessageType>* tasks[N_TASKS] = {
    lightsControllerTask,
    irrigationControllerTask,
    serviceCommunicatorTask,
    applicationCommunicatorTask
};

void setup() {
    Serial.begin(9600);
    scheduler->init(50);
    for (uint8_t i = 0; i < N_TASKS; i++)
    {
        CommunicablePeriodBasedTask<MessageType>* task = tasks[i];
        task->init();
        scheduler->addPeriodBasedTask(task);
    }
}

void loop() {
    scheduler->schedule();
}