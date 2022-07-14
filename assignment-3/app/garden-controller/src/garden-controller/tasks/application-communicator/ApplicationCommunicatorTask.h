#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "iot/utils/bluetooth/MsgServiceBT.h"
#include "garden-controller/config/data/AppData.h"
#include "garden-controller/config/MessageType.h"
#include "garden-controller/tasks/service-communicator/ServiceCommunicatorTask.h"

enum class ApplicationCommunicatorTaskState : uint8_t {
    IDLE,
    READING
};

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

private:
    int _period = 100;
    AppData* appData;
    String message;
    MsgServiceBT* bluetooth;


public:

    ApplicationCommunicatorTask(AppData* appdata, uint8_t rxPin, uint8_t txPin) : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appdata;
        this->bluetooth = new MsgServiceBT(txPin, rxPin);
    }

    void init();
    void computeRead();
    void tick();

private:
    void onIdleState();
    void onReadingState();

    bool isMessagePresent();
};

#endif