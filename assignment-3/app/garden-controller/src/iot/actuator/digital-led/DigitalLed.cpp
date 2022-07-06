#include "DigitalLed.h"

DigitalLed::DigitalLed(uint8_t pin) {
  this->pin = pin;
}

void DigitalLed::setup() {
  pinMode(pin, OUTPUT);
}

void DigitalLed::setActive(bool isActive) {
  this->isActive = isActive;
  digitalWrite(pin, isActive ? HIGH : LOW);
}