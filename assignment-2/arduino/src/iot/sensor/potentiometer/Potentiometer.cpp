#include "Potentiometer.h"

Potentiometer::Potentiometer(uint8_t pin) {
    this->pin = pin;
}

void Potentiometer::setup() {
    pinMode(this->pin, INPUT);
}

void Potentiometer::computeRead() {
    this->potentiometerValue = analogRead(this->pin);
}

int Potentiometer::getValue() {
    return this->potentiometerValue;
}

uint8_t Potentiometer::getPercentage() {
    return map(this->getValue(), 0, 1023, 0, 100);
}