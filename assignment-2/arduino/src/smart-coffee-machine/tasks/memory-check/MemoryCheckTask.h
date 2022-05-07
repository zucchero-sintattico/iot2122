#ifndef _MEMORY_CHECK_TASK_H_
#define _MEMORY_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include <Arduino.h>
enum class MemoryCheckTaskState : uint8_t {
    CHECKING
};

class MemoryCheckTask : public CommunicablePeriodBasedTaskWithFSM<MemoryCheckTaskState, MessageType> {

private:
    int _period = 5000;
public:

    MemoryCheckTask() : MemoryCheckTask(this->_period) {}
    MemoryCheckTask(int period) : CommunicablePeriodBasedTaskWithFSM(MemoryCheckTaskState::CHECKING) {
        PeriodBasedTask::setPeriod(period);
    }

    void init();
    void computeRead();
    void tick();

};

#endif