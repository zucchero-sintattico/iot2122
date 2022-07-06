#include "ServiceCommunicatorTask.h"

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

bool ServiceCommunicatorTask::isStatusMessage(String message) {
    return message.startsWith("STATUS:");
}

bool ServiceCommunicatorTask::isCommandMessage(String message) {
    return message.startsWith("COMMAND:");
}

Status ServiceCommunicatorTask::getNewStatus(String statusMessage) {
    statusMessage.replace("STATUS:", "");
    if (statusMessage.equals("AUTO")) {
        return Status::AUTO;
    }
    else if (statusMessage.equals("MANUAL")) {
        return Status::MANUAL;
    }
    else {
        return Status::ALARM;
    }
}

Command ServiceCommunicatorTask::getNewCommand(String commandMessage) {
    Command command;
    command.digitalLed1active = commandMessage.substring(8, 9) == "1";
    command.digitalLed2active = commandMessage.substring(9, 10) == "1";
    command.analogLed1value = commandMessage.substring(10, 11).toInt();
    command.analogLed2value = commandMessage.substring(11, 12).toInt();
    command.irrigatorValue = commandMessage.substring(12, 13).toInt();
    return command;
}

void ServiceCommunicatorTask::onIdleState() {
    if (isMessagePresent()) {
        if (isStatusMessage(this->message)) {
            Status status = getNewStatus(this->message);
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
}

void ServiceCommunicatorTask::onReadingState() {
    if (isMessagePresent()) {
        if (isStatusMessage(message)) {
            Status status = getNewStatus(message);
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
        else if (isCommandMessage(message)) {
            Command command = getNewCommand(message);
            this->appData->setDigitalLed1Active(command.digitalLed1active);
            this->appData->setDigitalLed2Active(command.digitalLed2active);
            this->appData->setAnalogLed1Value(command.analogLed1value);
            this->appData->setAnalogLed2Value(command.analogLed2value);
            this->appData->setIrrigationSpeed(command.irrigatorValue);
        }
    }
    setState(ServiceCommunicatorTaskState::SENDING);
}

void ServiceCommunicatorTask::onSendingState() {
    String message = IRRIGATOR_STATUS_MESSAGE(this - appData->isIrrigatorOpen());
}



