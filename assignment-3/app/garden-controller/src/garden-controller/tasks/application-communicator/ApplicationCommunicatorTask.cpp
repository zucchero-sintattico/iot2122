#include "ApplicationCommunicatorTask.h"

void ApplicationCommunicatorTask::init() {
    this->bluetooth->begin(9600);
}

void ApplicationCommunicatorTask::computeRead() {

}

void ApplicationCommunicatorTask::tick() {
    switch (this->getState())
    {
    case ApplicationCommunicatorTaskState::IDLE:
        this->onIdleState();
        break;
    case ApplicationCommunicatorTaskState::SENDING:
        this->onSendingState();
        break;
    case ApplicationCommunicatorTaskState::READING:
        this->onReadingState();
        break;
    }
}

void ApplicationCommunicatorTask::onIdleState() {

}

void ApplicationCommunicatorTask::onReadingState() {
    if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_AUTO_STATUS)) {

    }
}

void ApplicationCommunicatorTask::onSendingState() {

}



