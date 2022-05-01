
#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_
#include "iot/actuator/actuator.h"
#include "iot/utils/servo-timer-2/ServoTimer2.h"

class MotorManager : public Actuator {

    private:
    int pin;
    int pos = 0;
    ServoTimer2 servo;

    public:
    MotorManager(int pin);
    void setup();
    void rotateTo(int angle);
    void returnToStart();
    void goToEnd();
};

#endif // _MOTOR_MANAGER_
