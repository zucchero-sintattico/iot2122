#include "ApplicationCommunicatorTask.h"

void ApplicationCommunicatorTask::init() {
    MsgService.init();
}

void ApplicationCommunicatorTask::computeRead() {
    if (this->getState() == ApplicationCommunicatorTaskState::IDLE && MsgService.isMsgAvailable()) {
        Msg* msg = MsgService.receiveMsg();
        this->commandToExecute = String(msg->getContent());
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
    case ApplicationCommunicatorTaskState::RECOVER:
        this->onRecoverState();
        break;
    case ApplicationCommunicatorTaskState::REFILL:
        this->onRefillState();
        break;
    }
}


bool ApplicationCommunicatorTask::isCommandPresent() {
    return this->commandToExecute.length() > 0;
}

void ApplicationCommunicatorTask::onIdleState() {
    if (isCommandPresent()) {
        if (this->commandToExecute == RECOVER_MESSAGE) {
            this->setState(ApplicationCommunicatorTaskState::RECOVER);
        }
        if (this->commandToExecute == REFILL_MESSAGE) {
            this->setState(ApplicationCommunicatorTaskState::REFILL);
        }
        this->commandToExecute = "";
    }
    else {
        this->setState(ApplicationCommunicatorTaskState::SENDING);
    }
}

void ApplicationCommunicatorTask::onSendingState() {
    if (this->appData->getStatus() == Status::IDLE) {
        MsgService.sendMsg(IDLE_MESSAGE);
    }
    else if (this->appData->getStatus() == Status::WORKING) {
        MsgService.sendMsg(WORKING_MESSAGE);
    }
    else if (this->appData->getStatus() == Status::ASSISTANCE) {
        MsgService.sendMsg(ASSISTANCE_MESSAGE);
    }

    MsgService.sendMsg(INFO(
        this->appData->getAvailableItemCount(Beverage::COFFEE),
        this->appData->getAvailableItemCount(Beverage::TEA),
        this->appData->getAvailableItemCount(Beverage::CHOCOLATE)
    ));

    MsgService.sendMsg(SELFCHECK(this->appData->getSelfCheckPerformedCount()));

    this->setState(ApplicationCommunicatorTaskState::IDLE);
}
void ApplicationCommunicatorTask::onRecoverState() {
    this->getMessageBus()->push(MessageType::RECOVER);
    this->setState(ApplicationCommunicatorTaskState::IDLE);
}
void ApplicationCommunicatorTask::onRefillState() {
    this->appData->refill();
    this->setState(ApplicationCommunicatorTaskState::IDLE);
}