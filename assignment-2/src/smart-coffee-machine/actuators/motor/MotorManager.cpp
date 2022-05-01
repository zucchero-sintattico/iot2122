#include "MotorManager.h"
#include <Arduino.h>

MotorManager::MotorManager(int pin) {
  this->pin = pin;
}

void MotorManager::setup() {
  servo.attach(this->pin);
}

void MotorManager::rotateTo(int angle) {
  if (angle >= 0 && angle <= 180) {
    for (pos = 0; pos <= angle; pos += 1) {
      servo.write(pos);
      Serial.println(pos);
      delay(15);
    }
  }
}

void MotorManager::returnToStart() {
  if (pos != 0) {
    for (; pos >= 0; pos -= 1) {
      servo.write(pos);
      Serial.println(pos);
      delay(15);
    }
  }
}

void MotorManager::goToEnd() {
  if (pos != 180) {
    this->rotateTo(180);
  }
}
