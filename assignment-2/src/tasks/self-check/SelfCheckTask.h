#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum SelfCheckTaskState {
    SELF_CHECK_STATE_IDLE,
    SELF_CHECK_STATE_MECHANIC_CHECK,
    SELF_CHECK_STATE_TEMPERATURE_CHECK,
    SELF_CHECK_STATE_ASSISTANCE
};

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

public:
    int period = 50;
    SelfCheckTask() : CommunicablePeriodBasedTaskWithFSM(SELF_CHECK_STATE_IDLE) {}

    void init();
    void tick();

};

#endif