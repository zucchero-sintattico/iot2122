#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/sensors/thermometer/ThermometerManager.h"
#include "smart-coffee-machine/actuators/motor/MotorManager.h"

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

    MotorManager* motorManager;
    ThermometerManager* thermometerManager;

public:
    SelfCheckTask(int motorPin, int thermometer) : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {
        this->setPeriod(_period);
        this->motorManager = new MotorManager(motorPin);
        this->thermometerManager = new ThermometerManager(thermometer);
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