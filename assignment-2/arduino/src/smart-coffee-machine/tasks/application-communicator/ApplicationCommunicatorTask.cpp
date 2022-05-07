#include "ApplicationCommunicatorTask.h"

void ApplicationCommunicatorTask::init() {
    // MsgService.init();
}

void ApplicationCommunicatorTask::computeRead() {
    if (this->getState() == ApplicationCommunicatorTaskState::IDLE && MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();    
        this->commandToExecute = msg->getContent();
        delete msg;
    }
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
    case ApplicationCommunicatorTaskState::FIX:
        this->onFixState();
        break;
    case ApplicationCommunicatorTaskState::REFILL:
        this->onRefillState();
        break;
    }
}


void ApplicationCommunicatorTask::onIdleState() {
    // TODO: implement
}
void ApplicationCommunicatorTask::onSendingState() {
    // TODO: implement
}
void ApplicationCommunicatorTask::onFixState() {
    // TODO: implement
}
void ApplicationCommunicatorTask::onRefillState() {
    // TODO: implement
}