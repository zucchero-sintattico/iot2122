#include "ServiceCommunicatorTask.h"
#include "garden-controller/utilites/CommunicationUtilities.h"

#define DEFAULT_BUFFER_SIZE 32

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


void ServiceCommunicatorTask::onIdleState() {
    if (isMessagePresent() && CommunicationUtilities::isStatusUpdateMessage(this->message)) {
        Status status = CommunicationUtilities::getStatusUpdateMessage(this->message).status;
        this->appData->setStatus(status);
    }

    if (appData->getStatus() == Status::AUTO) {
        this->setState(ServiceCommunicatorTaskState::READING);
    }
    else {
        this->setState(ServiceCommunicatorTaskState::IDLE);
    }
}

void ServiceCommunicatorTask::onReadingState() {
    if (isMessagePresent()) {
        if (CommunicationUtilities::isStatusUpdateMessage(message)) {
            Status status = CommunicationUtilities::getStatusUpdateMessage(message).status;
            this->appData->setStatus(status);
        }
        else if (CommunicationUtilities::isUpdateMessage(message)) {
            UpdateMessage updateMessage = CommunicationUtilities::getUpdateMessage(message);
            this->appData->update(updateMessage.digitalLed1active, updateMessage.digitalLed2active, updateMessage.analogLed1value, updateMessage.analogLed2value, updateMessage.irrigatorValue);
        }
    }

    if (appData->getStatus() == Status::AUTO) {
        this->setState(ServiceCommunicatorTaskState::SENDING);
    }
    else {
        this->setState(ServiceCommunicatorTaskState::IDLE);
    }
}

void ServiceCommunicatorTask::onSendingState() {
    sendStatusToService();
    if (appData->getStatus() == Status::MANUAL || appData->getStatus() == Status::ALARM) {
        setState(ServiceCommunicatorTaskState::IDLE);
    }
    else {
        setState(ServiceCommunicatorTaskState::READING);
    }
}


// Utilities

void ServiceCommunicatorTask::sendStatusToService() {
    String message = CommunicationUtilities::getStatusMessageFromAppData(this->appData);
    MsgService.sendMsg(message);
}

bool ServiceCommunicatorTask::isMessagePresent() {
    return this->message.length() > 0;
}