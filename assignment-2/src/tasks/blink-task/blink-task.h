#ifndef _BLINK_TASK_H_
#define _BLINK_TASK_H_

#include "scheduling/task/task.h"

class BlinkTask : public Task {

    enum { ON, OFF } state;

    public:
    BlinkTask();
    BlinkTask(int period);
    void init();
    void tick();
};

#endif