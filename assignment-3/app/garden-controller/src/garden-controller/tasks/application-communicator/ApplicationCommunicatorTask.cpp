#include "ApplicationCommunicatorTask.h"
#include "garden-controller/utilites/CommunicationUtilities.h"

void ApplicationCommunicatorTask::init() {
    this->bluetooth->init();
}

void ApplicationCommunicatorTask::computeRead() {
    if (this->bluetooth->isMsgAvailable()) {
        Msg* msg = this->bluetooth->receiveMsg();
        this->message = msg->getContent();
        delete msg;
    }
    else {
        this->message = "";
    }
}

void ApplicationCommunicatorTask::tick() {
    switch (this->getState())
    {
    case ApplicationCommunicatorTaskState::IDLE:
        this->onIdleState();
        break;
    case ApplicationCommunicatorTaskState::READING:
        this->onReadingState();
        break;
    }
}

void ApplicationCommunicatorTask::onIdleState() {
    if (appData->getStatus() == Status::MANUAL) {
        setState(ApplicationCommunicatorTaskState::READING);
    }
}

void ApplicationCommunicatorTask::onReadingState() {
    if (isMessagePresent()) {
        Serial.println("Message from BT: " + message);
        if (CommunicationUtilities::isUpdateMessage(message)) {
            UpdateMessage* updateMessage = CommunicationUtilities::getUpdateMessage(message);
            this->appData->update(updateMessage->digitalLed1active, updateMessage->digitalLed2active, updateMessage->analogLed1value, updateMessage->analogLed2value, updateMessage->irrigatorValue);
            delete updateMessage;
        }
        else if (CommunicationUtilities::isCommandMessage(message)) {
            CommandMessage* commandMessage = CommunicationUtilities::getCommandMessage(message);
            switch (commandMessage->command)
            {
            case Commands::OPEN_IRRIGATOR:
                if ((appData->getIrrigatorStatus() == READY || appData->getStatus() == Status::MANUAL) && !this->getMessageBus()->isMessagePresent(MessageType::NOTIFY_OPEN_IRRIGATOR)) {
                    this->getMessageBus()->push(MessageType::NOTIFY_OPEN_IRRIGATOR);
                }
                break;
            case Commands::CLOSE_IRRIGATOR:
                if (appData->getIrrigatorStatus() == OPEN && !this->getMessageBus()->isMessagePresent(MessageType::NOTIFY_CLOSE_IRRIGATOR)) {
                    this->getMessageBus()->push(MessageType::NOTIFY_CLOSE_IRRIGATOR);
                }
                break;
            default:
                break;
            }
            delete commandMessage;
        }
    }

    if (appData->getStatus() == Status::AUTO || appData->getStatus() == Status::ALARM) {
        setState(ApplicationCommunicatorTaskState::IDLE);
    }

}

bool ApplicationCommunicatorTask::isMessagePresent() {
    return this->message.length() > 0;
}
