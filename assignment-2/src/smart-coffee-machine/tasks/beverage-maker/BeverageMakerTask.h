#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum class BeverageMakerTaskState {
    IDLE,
    MAKING,
    WAITING
};

class BeverageMakerTask : public CommunicablePeriodBasedTaskWithFSM<BeverageMakerTaskState, MessageType> {

    public:
    int period = 50;

    BeverageMakerTask() : CommunicablePeriodBasedTaskWithFSM(BeverageMakerTaskState::IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif