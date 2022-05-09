#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/device/Device.h"


enum class SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};


#define WAITING_TIME 90000

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

    private:
    int _period = 25;
    int elapsedTime = 0;

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