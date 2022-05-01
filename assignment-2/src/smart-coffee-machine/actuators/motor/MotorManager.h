#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_
#include "iot/actuator/Actuator.h"
#include <Arduino.h>

class MotorManager : public Actuator {

    private:
    int pin;
    int current_angle;

    public:
    MotorManager(int pin);
    void setup();
    bool rotateTo(int angle);
    bool returnToStart();
    bool goToEnd();
};

#endif // _MOTOR_MANAGER_