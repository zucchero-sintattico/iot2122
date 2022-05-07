#include "Servo.h"
#include <Arduino.h>

#define START_POSITION 0
#define END_POSITION 180

Motor::Motor(int pin) {
  this->pin = pin;
}

void Motor::setup() {
  servo.attach(this->pin);
}

void Motor::rotateTo(int angle) {
  if (angle >= 0 && angle <= 180) {
    servo.write(angle);
  }
}

void Motor::returnToStart() {
  if (current_angle != 0) {
    servo.write(START_POSITION);
  }
}

void Motor::goToEnd() {
  if (current_angle != 180) {
    this->rotateTo(END_POSITION);
  }
}
