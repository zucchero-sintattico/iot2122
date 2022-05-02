#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/sensors/pir/PirManager.h"

enum class PresenceTaskState {
    IDLE,
    NOONE,
    SOMEONE,
    SLEEP
};

class PresenceTask : public CommunicablePeriodBasedTaskWithFSM<PresenceTaskState, MessageType> {

    public:
        int period = 50;
    
    private:
        int pirPin;
        PirManager* pirManager;

    public:
    PresenceTask(int pirPin) : CommunicablePeriodBasedTaskWithFSM(PresenceTaskState::IDLE) {
        this->pirPin = pirPin;
        this->pirManager = new PirManager(pirPin);
    }

    void init();
    void computeRead();
    void tick();

    private:
    void onIdleState();
    void onNooneState();
    void onSomeoneState();
    void onSleepState();

};

#endif