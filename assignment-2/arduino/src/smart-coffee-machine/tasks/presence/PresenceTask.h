#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "iot/sensor/pir/Pir.h"

enum class PresenceTaskState {
    IDLE,
    NOONE,
    SOMEONE,
    SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

private:
    int pirPin;
    Pir* pirManager;
    int _period = 500;

    const int tickToSleep = 20;     // 20 tick * 500ms = 10s
    int elapsedTickNooneDetected = 0;

public:
    PresenceTask(int pirPin) : CommunicablePeriodBasedTaskWithFSM(PresenceTaskState::IDLE) {
        this->pirPin = pirPin;
        this->pirManager = new Pir(pirPin);
        this->setPeriod(this->_period);
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