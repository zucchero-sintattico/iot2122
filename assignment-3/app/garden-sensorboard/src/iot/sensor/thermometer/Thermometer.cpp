#include "Thermometer.h"

Thermometer::Thermometer(uint8_t pin) {
    this->pin = pin;
}

void Thermometer::setup() {
    temperature = 0;
    pinMode(pin, INPUT);
}

void Thermometer::computeRead() {
    int current_temperature = analogRead(this->pin);
    float voltage = current_temperature * AREF_VOLTAGE;
    voltage /= 1024.0;
    temperature = (voltage - 0.5) * 100;
}

uint8_t Thermometer::getTemperature() {
    return this->temperature;
}

String Thermometer::toString() {
    return getTemperature() + "°C";
}