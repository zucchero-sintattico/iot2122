#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum BeverageMakerTaskState {
    IDLE,
    MAKING,
    WAITING
};

class BeverageMakerTask : public CommunicablePeriodBasedTaskWithFSM<BeverageMakerTaskState, MessageType> {

public:
    static const int period = 50;

    BeverageMakerTask(MessageBus<MessageType>* messageBus) : CommunicablePeriodBasedTaskWithFSM(messageBus, BeverageMakerTaskState::IDLE) {}

    void init();
    void tick();

};

#endif