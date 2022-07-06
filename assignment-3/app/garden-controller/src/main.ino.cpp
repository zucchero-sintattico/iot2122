# 1 "C:\\Users\\alema\\AppData\\Local\\Temp\\tmp37r0ml_o"
#include <Arduino.h>
# 1 "C:/Users/alema/Desktop/iot2122/assignment-3/app/garden-controller/src/main.ino"
#include <Arduino.h>


#include "iot/scheduling/scheduler/SchedulerWithMessageBus.h"


#include "garden-controller/tasks/lights-controller/LightsControllerTask.h"
#include "garden-controller/tasks/irrigation-controller/IrrigationControllerTask.h"


#include "garden-controller/config/data/AppData.h"
#include "garden-controller/config/MessageType.h"
#include "garden-controller/config/device/Device.h"
#include "garden-controller/config/device/DeviceBuilder.h"



#define digitalLed1Pin 3
#define digitalLed2Pin 4
#define analogLed1Pin 5
#define analogLed2Pin 6
#define servoPin 9

DeviceBuilder* builder = new DeviceBuilder();
Device* device = builder
->withMotor(new Motor(servoPin))
->withDigitalLed1(new DigitalLed(digitalLed1Pin))
->withDigitalLed2(new DigitalLed(digitalLed2Pin))
->withAnalogLed1(new AnalogLed(analogLed1Pin))
->withAnalogLed2(new AnalogLed(analogLed2Pin))
->build();


AppData* appData = new AppData();


Scheduler* scheduler = new Scheduler();





LightsControllerTask* lightsControllerTask = new LightsControllerTask(appData, device);
IrrigationControllerTask* irrigationControllerTask = new IrrigationControllerTask(appData, device);

#define N_TASKS 2
CommunicablePeriodBasedTask<MessageType>* tasks[N_TASKS] = {
    lightsControllerTask,
    irrigationControllerTask
};
void setup();
void loop();
#line 52 "C:/Users/alema/Desktop/iot2122/assignment-3/app/garden-controller/src/main.ino"
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