#include <Arduino.h>

#define LED_PIN 25
#define PHOTORESISTOR_PIN 34
#define THERMOMETER_PIN 35


#include "garden-sensorboard/device/Device.h"
#include "garden-sensorboard/device/DeviceBuilder.h"

#include "garden-sensorboard/task/status/StatusManagerTask.h"
#include "garden-sensorboard/task/sensor/SensorManagerTask.h"

#include "iot/sensor/photoresistor/Photoresistor.h"

TaskHandle_t StatusManagerHandler;
TaskHandle_t SensorManagerHandler;

DeviceBuilder* builder = new DeviceBuilder();
Device* device = builder
->withDigitalLed(new DigitalLed(LED_PIN))
->withPhotoresistor(new Photoresistor(PHOTORESISTOR_PIN))
->withThermometer(new Thermometer(THERMOMETER_PIN))
->build();

StatusManagerTask* statusrManagerTask = new StatusManagerTask(0, device);
SensorManagerTask* sensorManagerTask = new SensorManagerTask(1000, device);

void StatusManagerTaskCode(void* pvParameters) {
    statusrManagerTask->run();
}

void SensorManagerTaskCode(void* pvParameters) {
    sensorManagerTask->run();
}

void setup(){
    Serial.begin(115200);
    device->setup();
    xTaskCreate(
        StatusManagerTaskCode, /* Function to implement the task */
        "statusTask", /* Name of the task */
        4096, /* Stack size in words */
        NULL, /* Task input parameter */
        1, /* Priority of the task */
        &StatusManagerHandler /* Task handle to keep track of created task */
    );
    xTaskCreate(
        SensorManagerTaskCode, /* Function to implement the task */
        "sensorTask", /* Name of the task */
        4096, /* Stack size in words */
        NULL, /* Task input parameter */
        1, /* Priority of the task */
        &SensorManagerHandler /* Task handle to keep track of created task */
    );
}

void loop() {}
