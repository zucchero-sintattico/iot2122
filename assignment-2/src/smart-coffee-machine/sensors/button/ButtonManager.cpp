#include "ButtonManager.h"
#include <Arduino.h>

ButtonManager::ButtonManager(int pin) {
    this->pin = pin;
}

void ButtonManager::setup() {
    pinMode(this->pin, INPUT);
}

void ButtonManager::computeRead() {
    bool value = digitalRead(this->pin);
    if (value == LOW && this->prevValue == HIGH) {
        this->isButtonPressed = true;
    }
    else {
        this->isButtonPressed = false;
    }
    this->prevValue = value;
}

bool ButtonManager::isPressed() {
    return this->isButtonPressed;
}