#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "../PeriodBasedTaskWithFSM.h"

enum BeverageSelectorTaskState {
    IDLE,
    READY,
    SELECTING,
    SELECTED,
    ASSISTANCE
};

class BeverageSelectorTask : public PeriodBasedTaskWithFSM<BeverageSelectorTaskState> {

public:
    static const int period = 50;
    BeverageSelectorTask() : PeriodBasedTaskWithFSM(BeverageSelectorTaskState::IDLE) {}

    void init();
    void tick();

};

#endif