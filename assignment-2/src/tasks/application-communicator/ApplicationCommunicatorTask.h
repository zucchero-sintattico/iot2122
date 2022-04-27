#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "../PeriodBasedTaskWithFSM.h"

enum ApplicationCommunicatorTaskState {
    IDLE,
    SENDING,
    FIX,
    REFILL
};

class ApplicationCommunicatorTask : public PeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState> {

public:
    static const int period = 50;

    ApplicationCommunicatorTask() : PeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {}

    void init();
    void tick();

};

#endif