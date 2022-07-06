#ifndef _MEMORY_CHECK_TASK_H_
#define _MEMORY_CHECK_TASK_H_

#include "iot/finite-state-machine/PeriodBasedTaskWithFSM.h"
#include "garden-controller/config/data/AppData.h"

#include <Arduino.h>
enum class MemoryCheckTaskState : uint8_t {
    CHECKING
};

class MemoryCheckTask : public PeriodBasedTaskWithFSM<MemoryCheckTaskState> {

    private:
    int _period = 1000;
    AppData* appData;
    public:

    MemoryCheckTask(AppData* appData) : PeriodBasedTaskWithFSM(MemoryCheckTaskState::CHECKING) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appData;
    }

    void init();
    void computeRead();
    void tick();

};

#endif