#ifndef _PERIOD_BASED_TASK_WITH_FSM_H_
#define _PERIOD_BASED_TASK_WITH_FSM_H_

#include "scheduling/task/PeriodBasedTask.h"
#include "finite-state-machine/FiniteStateMachine.h"

template<class S>
class PeriodBasedTaskWithFSM : public PeriodBasedTask, public FiniteStateMachine<S> {

    public:
    static const int period;

    PeriodBasedTaskWithFSM(S initialState) : FiniteStateMachine(initialState) {}

    virtual void init() = 0;
    virtual void tick() = 0;
};

#endif