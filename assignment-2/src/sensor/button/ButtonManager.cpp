#include "ButtonManager.h"
#include <Arduino.h>

ButtonManager::ButtonManager(int pin) {
    this->pin = pin;
}

void ButtonManager::setup() {
    pinMode(this->pin, INPUT);
}

void ButtonManager::computeRead() {
    this->isButtonPressed = digitalRead(this->pin);
}

bool ButtonManager::isPressed() {
    return this->isButtonPressed;
}