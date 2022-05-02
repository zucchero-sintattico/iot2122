#ifndef _COMMUNICABLE_PERIOD_BASED_TASK_H_
#define _COMMUNICABLE_PERIOD_BASED_TASK_H_

#include "./CommunicableTask.h"
#include "./PeriodBasedTask.h"

template<class M>
class CommunicablePeriodBasedTask : public CommunicableTask<M>, public PeriodBasedTask {

public:
    // Inherited from PeriodBasedTask
    virtual void init() = 0;
    virtual void computeRead() = 0;
    virtual void tick() = 0;

};

#endif