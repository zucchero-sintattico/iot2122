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