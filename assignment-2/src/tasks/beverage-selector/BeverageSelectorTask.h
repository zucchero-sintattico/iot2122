#ifndef _BEVERAGE_SELECTOR_TASK_H_
#define _BEVERAGE_SELECTOR_TASK_H_

#include "scheduling/task/PeriodBasedTask.h"

class BeverageSelectorTask : public PeriodBasedTask {

    public:
    static const int period = 10000;

    void init();
    void tick();

};

#endif