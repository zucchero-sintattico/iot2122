#include "PotentiometerManager.h"

PotentiometerManager::PotentiometerManager(int pin) {
    this->pin = pin;
}

void PotentiometerManager::setup() {
    pinMode(this->pin, INPUT);
}

void PotentiometerManager::computeRead() {
    this->potentiometerValue = analogRead(this->pin);
}

uint8_t PotentiometerManager::getValue() {
    return this->potentiometerValue;
}