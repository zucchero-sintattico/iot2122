#ifndef _PERIOD_BASED_TASK_WITH_FSM_H_
#define _PERIOD_BASED_TASK_WITH_FSM_H_

#include "../scheduling/task/CommunicablePeriodBasedTask.h"
#include "./FiniteStateMachine.h"


template<class S, class M>
class CommunicablePeriodBasedTaskWithFSM : public CommunicablePeriodBasedTask<M>, public FiniteStateMachine<S> {

    public:
    CommunicablePeriodBasedTaskWithFSM(S initialState) : FiniteStateMachine<S>(initialState) {}

    // Inherited from CommunicablePeriodBasedTask
    int period;
    virtual void init() = 0;
    virtual void computeRead() = 0;
    virtual void tick() = 0;
};

#endif