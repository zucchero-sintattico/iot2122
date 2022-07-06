#ifndef _APPLICATION_COMMUNICATOR_TASK_H_
#define _APPLICATION_COMMUNICATOR_TASK_H_

#include "iot/finite-state-machine/CommunicablePeriodBasedTaskWithFSM.h"
#include <Arduino.h>
#include <SoftwareSerial.h>
#include "iot/utils/serial/MsgService.h"
#include "garden-controller/config/data/AppData.h"
#include "garden-controller/config/MessageType.h"

enum class ApplicationCommunicatorTaskState : uint8_t {
    IDLE,
    READING,
    SENDING
};

class ApplicationCommunicatorTask : public CommunicablePeriodBasedTaskWithFSM<ApplicationCommunicatorTaskState, MessageType> {

    private:
    int _period = 500;
    AppData* appData;
    String message;
    SoftwareSerial* bluetooth;

    public:

    ApplicationCommunicatorTask(AppData* appdata, uint8_t rxPin, uint8_t txPin) : CommunicablePeriodBasedTaskWithFSM(ApplicationCommunicatorTaskState::IDLE) {
        PeriodBasedTask::setPeriod(this->_period);
        this->appData = appdata;
        this->bluetooth = new SoftwareSerial(rxPin, txPin);
    }

    void init();
    void computeRead();
    void tick();

    void onIdleState();
    void onReadingState();
    void onSendingState();

};

#endif