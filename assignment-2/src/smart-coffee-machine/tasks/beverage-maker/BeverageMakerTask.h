#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum BeverageMakerTaskState {
    BEVERAGE_MAKER_STATE_IDLE,
    BEVERAGE_MAKER_STATE_MAKING,
    BEVERAGE_MAKER_STATE_WAITING
};

class BeverageMakerTask : public CommunicablePeriodBasedTaskWithFSM<BeverageMakerTaskState, MessageType> {

    public:
    int period = 50;

    BeverageMakerTask() : CommunicablePeriodBasedTaskWithFSM(BEVERAGE_MAKER_STATE_IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif