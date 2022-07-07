#include "ServiceCommunicatorTask.h"
#include "garden-controller/utilites/CommunicationUtilities.h"

void ServiceCommunicatorTask::init() {
    MsgService.init(DEFAULT_BUFFER_SIZE);
}

void ServiceCommunicatorTask::computeRead() {
    if (MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        this->message = String(msg->getContent());
        delete msg;
    }
}

void ServiceCommunicatorTask::tick() {
    switch (this->getState())
    {
    case ServiceCommunicatorTaskState::IDLE:
        this->onIdleState();
        break;
    case ServiceCommunicatorTaskState::SENDING:
        this->onSendingState();
        break;
    case ServiceCommunicatorTaskState::READING:
        this->onReadingState();
        break;
    }
}

bool ServiceCommunicatorTask::isMessagePresent() {
    return this->message.length() > 0;
}

void ServiceCommunicatorTask::onIdleState() {
    if (isMessagePresent()) {
        if (CommunicationUtilities::isStatusUpdateMessage(this->message)) {
            Status status = CommunicationUtilities::getStatusUpdateMessage(this->message).status;
            if (status != this->appData->getStatus()) {
                this->appData->setStatus(status);
                if (status == Status::AUTO) {
                    getMessageBus()->push(MessageType::NOTIFY_AUTO_STATUS);
                    setState(ServiceCommunicatorTaskState::READING);
                }
                else if (status == Status::MANUAL) {
                    getMessageBus()->push(MessageType::NOTIFY_MANUAL_STATUS);
                }
                else if (status == Status::ALARM) {
                    getMessageBus()->push(MessageType::NOTIFY_ALARM_STATUS);
                }
            }
        }
    }
    sendStatusToService();
}

void ServiceCommunicatorTask::onReadingState() {
    if (isMessagePresent()) {
        if (CommunicationUtilities::isStatusUpdateMessage(message)) {
            Status status = CommunicationUtilities::getStatusUpdateMessage(message).status;
            if (status != this->appData->getStatus()) {
                this->appData->setStatus(status);
                if (status == Status::MANUAL) {
                    getMessageBus()->push(MessageType::NOTIFY_MANUAL_STATUS);
                }
                else if (status == Status::ALARM) {
                    getMessageBus()->push(MessageType::NOTIFY_ALARM_STATUS);
                }
                setState(ServiceCommunicatorTaskState::IDLE);
            }
        }
        else if (CommunicationUtilities::isUpdateMessage(message)) {
            UpdateMessage updateMessage = CommunicationUtilities::getUpdateMessage(message);
            this->appData->update(updateMessage.digitalLed1active, updateMessage.digitalLed2active, updateMessage.analogLed1value, updateMessage.analogLed2value, updateMessage.irrigatorValue);
        }
    }
    setState(ServiceCommunicatorTaskState::SENDING);
}

void ServiceCommunicatorTask::onSendingState() {
    sendStatusToService();
    setState(ServiceCommunicatorTaskState::READING);
}

void ServiceCommunicatorTask::sendStatusToService() {
    String message = CommunicationUtilities::getStatusMessageFromAppData(this->appData);
    MsgService.sendMsg(message);
}

String formatStatusFromAppData(AppData* appData) {
    return String(
        String(appData->isDigitalLed1Active() ? "1" : "0") + "," +
        String(appData->isDigitalLed2Active() ? "1" : "0") + "," +
        String(appData->getAnalogLed1Value()) + "," +
        String(appData->getAnalogLed2Value()) + "," +
        String(appData->isIrrigatorOpen() ? "1" : "0") + "," +
        String(appData->getIrrigationSpeed())
    );
}

