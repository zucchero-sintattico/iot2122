#ifndef _MOTOR_MANAGER_H_
#define _MOTOR_MANAGER_H_
#include "../SensorManager.h"

class MotorManager : public SensorManager{

    private:
        int pin;
        int current_angle;

    public:
        MotorManager(int pin);
        void setup();
        void computeRead();
        bool rotateTo(int angle);
        bool returnToStart();
        bool goToEnd();
};

#endif // _MOTOR_MANAGER_