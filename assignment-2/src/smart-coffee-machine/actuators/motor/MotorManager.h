#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_
#include "iot/actuator/actuator.h"
#include <Servo.h>

class MotorManager : public Actuator {

    private:
    int pin;
    int current_angle = 0;
    Servo servo;

    public:
    MotorManager(int pin);
    void setup();
    void rotateTo(int angle);
    void returnToStart();
    void goToEnd();
};

#endif // _MOTOR_MANAGER_