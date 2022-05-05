#include "PirManager.h"
#include <Arduino.h>

PirManager::PirManager(int pin) {
    this->pin = pin;
}

void PirManager::setup() {
    pinMode(this->pin, INPUT);
    delay(calibrationTimeMS);   // Wait for calibration
}

void PirManager::computeRead() {
    this->detection = digitalRead(this->pin);
}

bool PirManager::isSomeoneDetected() {
    return this->detection;
}