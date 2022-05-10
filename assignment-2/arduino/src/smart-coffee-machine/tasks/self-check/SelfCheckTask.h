#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/device/Device.h"
#include "smart-coffee-machine/config/data/AppData.h"


enum class SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};


#define WAITING_TIME 30000

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

    private:
    int _period = 50;
    int elapsedTime = 0;

    uint8_t incrementFactor = 2;
    int totalRotation = 0;
    uint8_t angle = 0;
    uint8_t increment;

    CoffeeDisplayI2C* display;
    Motor* motor;
    Thermometer* thermometerManager;

    AppData* appData;

    public:
    SelfCheckTask(AppData* appData, Device* device) : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {
        PeriodBasedTask::setPeriod(_period);
        this->motor = device->getMotor();
        this->thermometerManager = device->getThermometer();
        this->display = device->getCoffeeDisplayI2C();
        this->appData = appData;
        this->increment = incrementFactor;
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