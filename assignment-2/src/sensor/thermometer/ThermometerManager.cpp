#include "ThermometerManager.h"

ThermometerManager::ThermometerManager(int pin) {
    this->pin = pin;
}

void ThermometerManager::setup() {
    temperature = 0;
    pinMode(pin, INPUT);
}

void ThermometerManager::computeRead() {
    int current_temperature = analogRead(this->pin);
    float voltage = current_temperature * AREF_VOLTAGE;
    voltage /= 1024.0;
    temperature = (voltage - 0.5) * 100;
}

uint8_t ThermometerManager::getTemperature() {
    return this->temperature;
}

String ThermometerManager::toString() {
    return getTemperature() + "°C";
}