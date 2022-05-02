#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum class SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

private:
    int _period = 100;

public:
    SelfCheckTask() : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {
        this->setPeriod(_period);
    }

    void init();
    void computeRead();
    void tick();

};

#endif