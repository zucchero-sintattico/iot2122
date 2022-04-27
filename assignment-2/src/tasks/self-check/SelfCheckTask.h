#ifndef _SELF_CHECK_TASK_H_
#define _SELF_CHECK_TASK_H_

#include "scheduling/task/Task.h"

class SelfCheckTask : public Task {

public:
    void init();
    void tick();

};

#endif