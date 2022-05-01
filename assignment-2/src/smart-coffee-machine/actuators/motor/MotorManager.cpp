#include "MotorManager.h"
#include <Arduino.h>

MotorManager::MotorManager(int pin) {
    this->pin = pin;
}

void MotorManager::setup() {
    pinMode(pin, OUTPUT);
}

bool MotorManager::rotateTo(int angle) {
    digitalWrite(pin, HIGH);
    delayMicroseconds(angle);
}

bool MotorManager::returnToStart() {
    if (current_angle != 0) {
        rotateTo(0);
    }
}

bool MotorManager::goToEnd() {
    if (current_angle != 180) {
        rotateTo(180);
    }
}