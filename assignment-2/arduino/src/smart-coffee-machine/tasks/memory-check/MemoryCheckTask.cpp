#include "MemoryCheckTask.h"

#include "iot/utils/memory/FreeMemory.h"

void MemoryCheckTask::init() {}

void MemoryCheckTask::computeRead() {}

void MemoryCheckTask::tick() {
    Serial.println("MEMORY:" + String(freeMemory()));
}