#ifndef _PERIOD_BASED_TASK_WITH_FSM_H_
#define _PERIOD_BASED_TASK_WITH_FSM_H_

#include "../scheduling/task/PeriodBasedTask.h"
#include "./FiniteStateMachine.h"


template<class S>
class PeriodBasedTaskWithFSM : public PeriodBasedTask, public FiniteStateMachine<S> {

    public:
    PeriodBasedTaskWithFSM(S initialState) : FiniteStateMachine<S>(initialState) {}
};

#endif