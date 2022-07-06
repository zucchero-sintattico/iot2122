#include "AnalogLed.h"

AnalogLed::AnalogLed(uint8_t pin) {
  this->pin = pin;
}

void AnalogLed::setup() {
  pinMode(pin, OUTPUT);
}

void AnalogLed::setValue(uint8_t value) {
  this->value = value;
  analogWrite(pin, value);
}