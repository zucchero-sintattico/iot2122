#include "Pir.h"
#include <Arduino.h>

Pir::Pir(int pin) {
    this->pin = pin;
}

void Pir::setup() {
    pinMode(this->pin, INPUT);
    delay(calibrationTimeMS);   // Wait for calibration
}

void Pir::computeRead() {
    this->detection = digitalRead(this->pin);
}

bool Pir::isSomeoneDetected() {
    return this->detection;
}