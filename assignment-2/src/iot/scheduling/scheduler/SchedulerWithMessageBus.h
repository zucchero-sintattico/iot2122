#ifndef _SCHEDULER_WITH_MESSAGE_BUS_H_
#define _SCHEDULER_WITH_MESSAGE_BUS_H_

#include "./Scheduler.h"
#include "../strategy/SchedulingStrategies.h"
#include "../../communication/MessageBus.h"
#include "../task/CommunicablePeriodBasedTask.h"
#include "../task/CommunicableTask.h"

template<class M>
class SchedulerWithMessageBus : public Scheduler {

private:
    MessageBus<M>* messageBus;
public:
    SchedulerWithMessageBus() {
        this->messageBus = new MessageBus<M>();
    }
    SchedulerWithMessageBus(MessageBus<M>* messageBus) : messageBus(messageBus) {}

    bool addTask(CommunicableTask<M>* task, SchedulingStrategy* schedulingStrategy) {
        task->attachMessageBus(messageBus);
        return Scheduler::addTask(task, schedulingStrategy);
    }

    bool addPeriodBasedTask(CommunicablePeriodBasedTask<M>* task) {
        Serial.println("Adding task with PERIOD = " + String(task->getPeriod()));
        return this->addTask(task, SchedulingStrategies::FromPeriod(task->getPeriod()));
    }

};

#endif