#include "ApplicationCommunicatorTask.h"

#include "iot/utils/memory/FreeMemory.h"

void ApplicationCommunicatorTask::init() {
    // do stuff...
}

void ApplicationCommunicatorTask::computeRead() {
    // do stuff...
}

void ApplicationCommunicatorTask::tick() {
    Serial.println("Free Memory: " + String(freeMemory()));
}