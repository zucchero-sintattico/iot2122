#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum SelfCheckTaskState {
    IDLE,
    MECHANIC_CHECK,
    TEMPERATURE_CHECK,
    ASSISTANCE
};

class SelfCheckTask : public CommunicablePeriodBasedTaskWithFSM<SelfCheckTaskState, MessageType> {

public:
    static const int period = 50;
    SelfCheckTask(MessageBus<MessageType>* messageBus) : CommunicablePeriodBasedTaskWithFSM(messageBus, SelfCheckTaskState::IDLE) {}

    void init();
    void tick();

};

#endif