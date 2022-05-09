#ifndef _MEMORY_CHECK_TASK_H_
#define _MEMORY_CHECK_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"

#include "smart-coffee-machine/config/data/AppData.h"

#include <Arduino.h>
enum class MemoryCheckTaskState : uint8_t {
    CHECKING
};

class MemoryCheckTask : public CommunicablePeriodBasedTaskWithFSM<MemoryCheckTaskState, MessageType> {

    private:
    int _period = 1000;
    AppData* appData;
    public:

    MemoryCheckTask(AppData* appData) : CommunicablePeriodBasedTaskWithFSM(MemoryCheckTaskState::CHECKING) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
    }

    void init();
    void computeRead();
    void tick();

};

#endif