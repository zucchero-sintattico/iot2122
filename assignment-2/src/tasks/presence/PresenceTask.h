#ifndef _PRESENCE_TASK_H_
#define _PRESENCE_TASK_H_

#include "scheduling/task/Task.h"

class PresenceTask : public Task {
    void init();
    void tick();
};

#endif