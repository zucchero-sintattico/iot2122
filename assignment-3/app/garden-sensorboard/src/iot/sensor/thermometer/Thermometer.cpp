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
    if (temperature < 10) {
        temperature = 10;
    }
    else if (temperature > 60) {
        temperature = 60;
    }
    temperature = map(temperature, 10, 60, 1, 5);
}

uint8_t Thermometer::getTemperature() {
    return this->temperature;
}

String Thermometer::toString() {
    return getTemperature() + "°C";
}