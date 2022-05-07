
#ifndef _SERVO_H_
#define _SERVO_H_
#include "iot/actuator/actuator.h"
#include <Servo.h>

class Motor : public Actuator {

private:
    int pin;
    int current_angle = 0;
    Servo servo;

public:
    Motor(int pin);
    void setup();
    void rotateTo(int angle);
    void returnToStart();
    void goToEnd();
};

#endif // _MOTOR_MANAGER_
