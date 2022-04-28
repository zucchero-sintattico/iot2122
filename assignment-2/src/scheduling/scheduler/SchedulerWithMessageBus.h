#ifndef _SCHEDULER_WITH_MESSAGE_BUS_H_
#define _SCHEDULER_WITH_MESSAGE_BUS_H_

#include "Scheduler.h"
#include "scheduling/strategy/SchedulingStrategies.h"
#include "communication/MessageBus.h"
#include "scheduling/task/CommunicablePeriodBasedTask.h"
#include "scheduling/task/CommunicableTask.h"

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
        Serial.println("ATTACH BUS");
        task->attachMessageBus(messageBus);
        return Scheduler::addTask(task, schedulingStrategy);
    }

    bool addPeriodBasedTask(CommunicablePeriodBasedTask<M>* task) {
        return this->addTask(task, SchedulingStrategies::FromPeriod(task->period));
    }

};

#endif