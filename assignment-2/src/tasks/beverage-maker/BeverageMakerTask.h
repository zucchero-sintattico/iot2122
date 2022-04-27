#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "../PeriodBasedTaskWithFSM.h"

enum BeverageMakerTaskState {
    IDLE,
    MAKING,
    WAITING
};

class BeverageMakerTask : public PeriodBasedTaskWithFSM<BeverageMakerTaskState> {

public:
    static const int period = 50;

    BeverageMakerTask() : PeriodBasedTaskWithFSM(BeverageMakerTaskState::IDLE) {}

    void init();
    void tick();

};

#endif