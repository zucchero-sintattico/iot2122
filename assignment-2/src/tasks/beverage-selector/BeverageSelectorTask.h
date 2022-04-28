#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_


#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum BeverageSelectorTaskState {
    IDLE,
    READY,
    SELECTING,
    SELECTED,
    ASSISTANCE
};

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

public:
    static const int period = 50;
    BeverageSelectorTask(MessageBus<MessageType>* messageBus) : CommunicablePeriodBasedTaskWithFSM(messageBus, BeverageSelectorTaskState::IDLE) {}

    void init();
    void tick();

};

#endif