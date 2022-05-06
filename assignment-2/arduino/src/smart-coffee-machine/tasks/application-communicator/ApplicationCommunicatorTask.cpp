#include "ApplicationCommunicatorTask.h"

void ApplicationCommunicatorTask::init() {
    // do stuff...
}

void ApplicationCommunicatorTask::computeRead() {
    // do stuff...
}

void ApplicationCommunicatorTask::tick() {
    this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
    this->getMessageBus()->print();
}