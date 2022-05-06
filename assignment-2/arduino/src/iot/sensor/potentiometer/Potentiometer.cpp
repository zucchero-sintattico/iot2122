#include "Potentiometer.h"

Potentiometer::Potentiometer(int pin) {
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