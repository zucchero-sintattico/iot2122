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

    public:
    int period = 50;
    SelfCheckTask() : CommunicablePeriodBasedTaskWithFSM(SelfCheckTaskState::IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif