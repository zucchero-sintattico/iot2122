#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "smart-coffee-machine/config/MessageType.h"
#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>
#include "iot/utils/serial/MsgService.h"
#include "smart-coffee-machine/config/data/AppData.h"

enum class ApplicationCommunicatorTaskState : uint8_t {
    IDLE,
    SENDING,
    RECOVER,
    REFILL
};

#define DEFAULT_BUFFER_SIZE 32

// App -> Arduino
#define REFILL_MESSAGE String("REFILL")
#define RECOVER_MESSAGE String("RECOVER")

// Arduino -> App
#define IDLE_MODALITY "IDLE"
#define WORKING_MODALITY "WORKING"
#define ASSISTANCE_MODALITY "ASSISTANCE"
#define INFO(MODALITY, COFFEE, TEA, CHOCOLATE, SELF_CHECK_COUNT, FREE_MEMORY) String("INFO:" + MODALITY + "," + COFFEE + "," + TEA + "," + CHOCOLATE + "," + SELF_CHECK_COUNT + "," + FREE_MEMORY)

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

    private:
    int _period = 1000;
    AppData* appData;
    String commandToExecute;

    public:

    ApplicationCommunicatorTask(AppData* appdata) : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appdata;
    }

    void init();
    void computeRead();
    void tick();

    void onIdleState();
    void onSendingState();
    void onRecoverState();
    void onRefillState();

    bool isCommandPresent();
};

#endif