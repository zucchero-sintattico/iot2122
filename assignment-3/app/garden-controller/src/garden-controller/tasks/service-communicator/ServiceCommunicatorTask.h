#ifndef _SERVICE_COMMUNICATOR_TASK_H_
#define _SERVICE_COMMUNICATOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>
#include "iot/utils/serial/MsgService.h"
#include "garden-controller/config/data/AppData.h"
#include "garden-controller/config/MessageType.h"

enum class ServiceCommunicatorTaskState : uint8_t {
    IDLE,
    READING,
    SENDING
};

class ServiceCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ServiceCommunicatorTaskState, MessageType> {

    private:
    int _period = 500;
    AppData* appData;
    String message;

    public:

    ServiceCommunicatorTask(AppData* appdata) : CommunicablePeriodBasedTaskWithFSM(ServiceCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appdata;
    }

    void init();
    void computeRead();
    void tick();

    private:
    void onIdleState();
    void onReadingState();
    void onSendingState();

    bool isMessagePresent();

    void sendStatusToService();

};

#endif