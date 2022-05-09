#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/device/Device.h"

#define MAX_PERIOD 3000

enum class SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};

#define TIME 3000

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

    private:
    int _period = 25;
    int elapsedTime = 0;
    const int tickForSelfCheck = 1000;
    int elapsedTicks = 0;

    uint8_t angle = 0;
    uint8_t increment = 1;

    CoffeeDisplayI2C* display;
    Motor* motor;
    Thermometer* thermometerManager;

    public:
    SelfCheckTask(Device* device) : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {
        PeriodBasedTask::setPeriod(_period);
        this->motor = device->getMotor();
        this->thermometerManager = device->getThermometer();
        this->display = device->getCoffeeDisplayI2C();
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