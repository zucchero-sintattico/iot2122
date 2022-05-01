#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_


#include "config/MessageType.h"
#include "../CommunicablePeriodBasedTaskWithFSM.h"

enum BeverageSelectorTaskState {
    BEVERAGE_SELECTOR_STATE_IDLE,
    BEVERAGE_SELECTOR_STATE_READY,
    BEVERAGE_SELECTOR_STATE_SELECTING,
    BEVERAGE_SELECTOR_STATE_SELECTED,
    BEVERAGE_SELECTOR_STATE_ASSISTANCE
};

class BeverageSelectorTask : public CommunicablePeriodBasedTaskWithFSM<BeverageSelectorTaskState, MessageType> {

    public:
    int period = 50;
    BeverageSelectorTask() : CommunicablePeriodBasedTaskWithFSM(BEVERAGE_SELECTOR_STATE_IDLE) {}

    void init();
    void computeRead();
    void tick();

};

#endif