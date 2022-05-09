#include "Pir.h"

Pir::Pir(uint8_t pin) {
    this->pin = pin;
}

uint8_t Pir::getPin() {
    return this->pin;
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