#include "IrrigationControllerTask.h"

void IrrigationControllerTask::init() {
    this->motor->setup();
}

void IrrigationControllerTask::computeRead() {

}

void IrrigationControllerTask::tick() {
    switch (this->getState())
    {
    case IrrigationControllerTaskState::OPEN:
        this->onOpenState();
        break;
    case IrrigationControllerTaskState::CLOSED:
        this->onClosedState();
        break;
    case IrrigationControllerTaskState::IDLE:
        this->onIdleState();
        break;
    }
}

void IrrigationControllerTask::onOpenState() {
    if (hasToBeClosed()) {
        changeStateToClosed();
    }
    else {
        rotate();
    }
}

void IrrigationControllerTask::onClosedState() {
    if (hasToBeOpened()) {
        changeStateToOpen();
    }
}

void IrrigationControllerTask::onIdleState() {
    if (hasToBeOpened()) {
        changeStateToOpen();
    }
}


// Utils

bool IrrigationControllerTask::hasToBeClosed() {
    if (getState() == IrrigationControllerTaskState::CLOSED || getState() == IrrigationControllerTaskState::IDLE) {
        return false;
    }
    if (appData->getStatus() == ALARM) {
        return true;
    }
    if (appData->getStatus() == AUTO) {
        long elapsedTimeSinceOpened = millis() - this->openTimestamp;
        return elapsedTimeSinceOpened > this->OPEN_TIME_MILLISECONDS;
    }
    bool isThereCommand = this->getMessageBus()->isMessagePresent(MessageType::NOTIFY_CLOSE_IRRIGATOR);
    if (isThereCommand) {
        this->getMessageBus()->removeMessage(MessageType::NOTIFY_CLOSE_IRRIGATOR);
    }
    return isThereCommand;
}

bool IrrigationControllerTask::hasToBeOpened() {
    if (getState() == IrrigationControllerTaskState::OPEN) {
        return false;
    }
    if (getState() == IrrigationControllerTaskState::IDLE) {
        return this->appData->getStatus() == Status::AUTO;
    }
    if (appData->getStatus() == ALARM) {
        return false;
    }
    if (appData->getStatus() == AUTO) {
        long elapsedTimeSinceOpened = millis() - this->closeTimestamp;
        return elapsedTimeSinceOpened > this->CLOSED_TIME_MILLISECONDS;
    }
    bool isThereCommand = this->getMessageBus()->isMessagePresent(MessageType::NOTIFY_OPEN_IRRIGATOR);
    if (isThereCommand) {
        this->getMessageBus()->removeMessage(MessageType::NOTIFY_OPEN_IRRIGATOR);
    }
    return isThereCommand;

}

void IrrigationControllerTask::rotate() {
    this->angle += this->direction * this->appData->getIrrigationSpeed();
    if (this->angle > 180) {
        this->angle = 180;
        this->direction = -1;
    }
    else if (this->angle < 0) {
        this->angle = 0;
        this->direction = 1;
    }
    this->motor->rotateTo(this->angle);
}

void IrrigationControllerTask::changeStateToOpen() {
    this->appData->setIrrigatorOpen(true);
    this->openTimestamp = millis();
    this->setState(IrrigationControllerTaskState::OPEN);
}

void IrrigationControllerTask::changeStateToClosed() {
    this->appData->setIrrigatorOpen(false);
    this->closeTimestamp = millis();
    setState(IrrigationControllerTaskState::CLOSED);
}