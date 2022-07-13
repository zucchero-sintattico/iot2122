#include "Thermometer.h"

Thermometer::Thermometer(uint8_t pin) {
    this->pin = pin;
}

void Thermometer::setup() {
    temperature = 0;
    pinMode(pin, INPUT);
}

void Thermometer::computeRead() {
    float voltage = analogRead(this->pin);
    voltage /= 1023.0;
    temperature = (voltage - 0.5) * 100;
    temperature = map(temperature, 10, 60, 0, 4);
}

uint8_t Thermometer::getTemperature() {
    return this->temperature;
}

String Thermometer::toString() {
    return getTemperature() + "°C";
}