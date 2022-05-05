#define START_POSITION 0
#define END_POSITION 180
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
    servo.write(angle);
  }
}

void MotorManager::returnToStart() {
  if (current_angle != 0) {
    servo.write(START_POSITION);
  }
}

void MotorManager::goToEnd() {
  if (current_angle != 180) {
    this->rotateTo(END_POSITION);
  }
}
