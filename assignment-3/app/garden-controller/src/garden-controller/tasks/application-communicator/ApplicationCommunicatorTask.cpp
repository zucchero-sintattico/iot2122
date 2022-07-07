#include "ApplicationCommunicatorTask.h"
#include "garden-controller/utilites/CommunicationUtilities.h"

void ApplicationCommunicatorTask::init() {
    this->bluetooth->begin(9600);
}

void ApplicationCommunicatorTask::computeRead() {
    if (bluetooth->available()) {
        this->message = bluetooth->readStringUntil('\n');
        this->message.replace("\r", "");
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
    if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_MANUAL_STATUS)) {
        setState(ApplicationCommunicatorTaskState::READING);
    }
}

void ApplicationCommunicatorTask::onReadingState() {
    if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_AUTO_STATUS)) {
        setState(ApplicationCommunicatorTaskState::IDLE);
        return;
    }

    if (isMessagePresent()) {
        if (CommunicationUtilities::isUpdateMessage(message)) {
            UpdateMessage updateMessage = CommunicationUtilities::getUpdateMessage(message);
            this->appData->update(updateMessage.digitalLed1active, updateMessage.digitalLed2active, updateMessage.analogLed1value, updateMessage.analogLed2value, updateMessage.irrigatorValue);
        }
        else if (CommunicationUtilities::isCommandMessage(message)) {
            CommandMessage commandMessage = CommunicationUtilities::getCommandMessage(message);
            switch (commandMessage.command)
            {
            case Commands::OPEN_IRRIGATOR:
                getMessageBus()->push(MessageType::NOTIFY_OPEN_IRRIGATOR);
                break;
            case Commands::CLOSE_IRRIGATOR:
                getMessageBus()->push(MessageType::NOTIFY_CLOSE_IRRIGATOR);
                break;
            }
        }
    }

    if (appData->getStatus() == Status::AUTO) {
        setState(ApplicationCommunicatorTaskState::IDLE);
    }

}

bool ApplicationCommunicatorTask::isMessagePresent() {
    return this->message.length() > 0;
}
