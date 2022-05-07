#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "iot/sensor/thermometer/Thermometer.h"
#include "iot/actuator/servo/Servo.h"

enum class SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

private:
    int _period = 100;

    const int tickForSelfCheck = 1000;
    int elapsedTicks = 0;

    Motor* servoManager;
    Thermometer* thermometerManager;

public:
    SelfCheckTask(uint8_t motorPin, uint8_t thermometer) : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {
        this->setPeriod(_period);
        this->servoManager = new Motor(motorPin);
        this->thermometerManager = new Thermometer(thermometer);
    }

    void init();
    void computeRead();
    void tick();

private:
    void onIdleState();
    void onMechanicCheckState();
    void onTemperatureCheckState();
    void onAssistanceState();

};

#endif