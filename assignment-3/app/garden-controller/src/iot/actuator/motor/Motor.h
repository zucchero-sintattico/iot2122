
#ifndef _SERVO_H_
#define _SERVO_H_
#include "iot/actuator/actuator.h"
#include <Servo.h>
#include <Arduino.h>

class Motor : public Actuator {

private:
    uint8_t pin;
    uint8_t current_angle = 0;
    Servo servo;

public:
    Motor(uint8_t pin);
    void setup();
    void rotateTo(uint8_t angle);
    void returnToStart();
    void goToEnd();
};

#endif // _MOTOR_MANAGER_
