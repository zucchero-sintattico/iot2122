#include "Servo.h"
#include <Arduino.h>

#define START_POSITION 0
#define END_POSITION 180

Servo::Servo(int pin) {
  this->pin = pin;
}

void Servo::setup() {
  servo.attach(this->pin);
}

void Servo::rotateTo(int angle) {
  if (angle >= 0 && angle <= 180) {
    servo.write(angle);
  }
}

void Servo::returnToStart() {
  if (current_angle != 0) {
    servo.write(START_POSITION);
  }
}

void Servo::goToEnd() {
  if (current_angle != 180) {
    this->rotateTo(END_POSITION);
  }
}
