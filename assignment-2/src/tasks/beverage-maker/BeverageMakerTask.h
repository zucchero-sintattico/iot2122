#ifndef _BEVERAGE_MAKER_TASK_H_
#define _BEVERAGE_MAKER_TASK_H_

#include "scheduling/task/PeriodBasedTask.h"

class BeverageMakerTask : public PeriodBasedTask {

    public:
    static const int period = 10000;

    void init();
    void tick();

};

#endif