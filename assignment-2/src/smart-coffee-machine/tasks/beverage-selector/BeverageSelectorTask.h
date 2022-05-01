#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

enum class BeverageSelectorTaskState {
    IDLE,
    READY,
    SELECTING,
    SELECTED,
    ASSISTANCE
};

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

    public:
    int period = 50;
    BeverageSelectorTask() : CommunicablePeriodBasedTaskWithFSM(BeverageSelectorTaskState::IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif