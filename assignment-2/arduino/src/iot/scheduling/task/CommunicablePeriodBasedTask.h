#ifndef _COMMUNICABLE_PERIOD_BASED_TASK_H_
#define _COMMUNICABLE_PERIOD_BASED_TASK_H_

#include "./CommunicableTask.h"
#include "./PeriodBasedTask.h"

template<class M>
class CommunicablePeriodBasedTask : public Communicable<M>, public PeriodBasedTask {};

#endif