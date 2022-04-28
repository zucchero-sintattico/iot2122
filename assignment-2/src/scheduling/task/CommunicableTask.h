#ifndef _COMMUNICABLE_TASK_H_
#define _COMMUNICABLE_TASK_H_

#include "./Task.h"
#include "communication/Communicable.h"

template<class M>
class CommunicableTask : public Task, public Communicable<M> {

public:
    CommunicablePeriodBasedTask(MessageBus<M>* messageBus) : Communicable<M>(messageBus) {}

    // Inherited from Task
    virtual void init() = 0;
    virtual void tick() = 0;

};

#endif