
#ifndef _SERVO_H_
#define _SERVO_H_
#include "iot/actuator/actuator.h"
#include "iot/utils/servo-timer-2/ServoTimer2.h"

class Servo : public Actuator {

private:
    int pin;
    int current_angle = 0;
    ServoTimer2 servo;

public:
    Servo(int pin);
    void setup();
    void rotateTo(int angle);
    void returnToStart();
    void goToEnd();
};

#endif // _MOTOR_MANAGER_
