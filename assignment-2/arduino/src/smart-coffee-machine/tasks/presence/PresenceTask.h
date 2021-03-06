#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/device/Device.h"

enum class PresenceTaskState : uint8_t {
    IDLE,
    NOONE,
    SOMEONE,
    SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

    private:
    int _period = 500;

    // Sensors
    Pir* pirManager;
    CoffeeDisplayI2C* display;

    const int tickToSleep = 20;     // 20 tick * 500ms = 10s
    int elapsedTickNooneDetected = 0;

    public:
    PresenceTask(Device* device) : CommunicablePeriodBasedTaskWithFSM(PresenceTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->pirManager = device->getPir();
        this->display = device->getCoffeeDisplayI2C();
    }

    void init();
    void computeRead();
    void tick();

    private:
    void onIdleState();
    void onNooneState();
    void onSomeoneState();
    void onSleepState();

    bool needIdleState();
};

#endif