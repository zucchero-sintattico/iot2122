#ifndef _MEMORY_CHECK_TASK_H_
#define _MEMORY_CHECK_TASK_H_

#include "garden-controller/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "garden-controller/config/data/AppData.h"

#include <Arduino.h>
enum class MemoryCheckTaskState : uint8_t {
    CHECKING
};

class MemoryCheckTask : public CommunicablePeriodBasedTaskWithFSM<MemoryCheckTaskState, MessageType> {

private:
    int _period = 1000;
public:

    MemoryCheckTask() : CommunicablePeriodBasedTaskWithFSM(MemoryCheckTaskState::CHECKING) {
        PeriodBasedTask::setPeriod(this->_period);
    }

    void init();
    void computeRead();
    void tick();

};

#endif