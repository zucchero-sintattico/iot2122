#ifndef _COMMUNICABLE_TASK_H_
#define _COMMUNICABLE_TASK_H_

#include "communication/Communicable.h"
#include "./Task.h"

template<class M>
class CommunicableTask : public Communicable<M>, public Task {

    public:
    // Inherited from PeriodBasedTask
    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif