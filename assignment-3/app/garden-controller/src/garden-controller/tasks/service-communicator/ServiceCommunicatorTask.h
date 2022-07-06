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

#define DEFAULT_BUFFER_SIZE 32

// Arduino -> App
#define IRRIGATOR_STATUS_MESSAGE(isOpen) (isOpen ? "1" : "0")

struct Command {
    bool digitalLed1active;
    bool digitalLed2active;
    uint8_t analogLed1value;
    uint8_t analogLed2value;
    uint8_t irrigatorValue;
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

    void onIdleState();
    void onReadingState();
    void onSendingState();

    bool isMessagePresent();

    bool isStatusMessage(String message);
    Status getNewStatus(String statusMessage);

    bool isCommandMessage(String message);
    Command getNewCommand(String commandMessage);

};

#endif