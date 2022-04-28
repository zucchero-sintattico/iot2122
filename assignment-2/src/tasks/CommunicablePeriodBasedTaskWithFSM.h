#ifndef _PERIOD_BASED_TASK_WITH_FSM_H_
#define _PERIOD_BASED_TASK_WITH_FSM_H_

#include "scheduling/task/CommunicablePeriodBasedTask.h"
#include "finite-state-machine/FiniteStateMachine.h"


template<class S, class M>
class CommunicablePeriodBasedTaskWithFSM : public CommunicablePeriodBasedTask<M>, public FiniteStateMachine<S> {

public:
    CommunicablePeriodBasedTaskWithFSM(MessageBus<M>* messageBus, S initialState) : CommunicablePeriodBasedTask<M>(messageBus) : FiniteStateMachine(initialState) {}

    // Inherited from CommunicablePeriodBasedTask
    static const int period;
    virtual void init() = 0;
    virtual void tick() = 0;
};

#endif