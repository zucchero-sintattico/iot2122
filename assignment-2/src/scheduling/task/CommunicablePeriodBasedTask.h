#ifndef _COMMUNICABLE_PERIOD_BASED_TASK_H_
#define _COMMUNICABLE_PERIOD_BASED_TASK_H_

#include "./CommunicableTask.h"
#include "./PeriodBasedTask.h"

template<class M>
class CommunicablePeriodBasedTask : public CommunicableTask<M>, public PeriodBasedTask {

public:
    CommunicablePeriodBasedTask(MessageBus<M>* messageBus) : CommunicableTask<M>(messageBus) {}

    // Inherited from PeriodBasedTask
    static const int period;
    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif