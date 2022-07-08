#include "Photoresistor.h"

Photoresistor::Photoresistor(uint8_t pin) {
    this->pin = pin;
}

void Photoresistor::setup() {
    light = 0;
    pinMode(pin, INPUT);
}

void Photoresistor::computeRead() {
    int value = analogRead(this->pin);
    light = map(value, 0, 4095, 0, 7);
}

uint8_t Photoresistor::getLight() {
    return this->light;
}
