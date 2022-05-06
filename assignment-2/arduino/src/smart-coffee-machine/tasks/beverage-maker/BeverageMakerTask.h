#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "iot/sensor/sonar/Sonar.h"
//#include "iot/actuator/servo/Servo.h"

#include "smart-coffee-machine/actuators/fake-coffee-display-i2c/FakeCoffeeDisplayI2C.h"


enum class BeverageMakerTaskState {
    IDLE,
    MAKING,
    WAITING
};

class BeverageMakerTask : public CommunicablePeriodBasedTaskWithFSM<BeverageMakerTaskState, MessageType> {

    static const int MAX_DISTANCE_IN_CM = 40;
    static const int INCREMENT_PERCENTAGE = 1;

private:
    int _period = 50;

    AppData* appData;

    // Sensors
    Sonar* sonar;

    // Actuators
    // Servo* servo;
    CoffeeDisplayI2C* display;

    int progressPercentage = 0;

public:

    BeverageMakerTask(AppData* appData, int trigPin, int echoPin, int servoPin) : CommunicablePeriodBasedTaskWithFSM(BeverageMakerTaskState::IDLE) {

        PeriodBasedTask::setPeriod(this->_period);

        this->appData = appData;

        this->sonar = new Sonar(trigPin, echoPin);
        //this->servo = new Servo(servoPin);
        this->display = FakeCoffeeDisplayI2C::getInstance();
    }

    void init();
    void computeRead();
    void tick();

private:
    void onIdleState();
    void onMakingState();
    void onWaitingState();

};

#endif