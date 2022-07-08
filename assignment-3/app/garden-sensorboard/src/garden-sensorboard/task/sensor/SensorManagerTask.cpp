#include "SensorManagerTask.h"

void SensorManagerTask::loop() {
    device->computeRead();

    Serial.print(device->getPhotoresistor()->getLight());
    // TODO: send data via MQTT
}