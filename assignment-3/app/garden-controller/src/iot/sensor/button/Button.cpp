#include "Button.h"
#include <Arduino.h>

Button::Button(uint8_t pin) {
    this->pin = pin;
}

void Button::setup() {
    pinMode(this->pin, INPUT);
}

void Button::computeRead() {
    bool value = digitalRead(this->pin);
    if (value == LOW && this->prevValue == HIGH) {
        this->isButtonPressed = true;
    }
    else {
        this->isButtonPressed = false;
    }
    this->prevValue = value;
}

bool Button::isPressed() {
    return this->isButtonPressed;
}