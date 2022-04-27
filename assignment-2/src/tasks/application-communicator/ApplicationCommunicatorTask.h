#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "scheduling/task/PeriodBasedTask.h"

class ApplicationCommunicatorTask : public PeriodBasedTask {

    public:
    static const int period = 50;

    void init();
    void tick();

};

#endif