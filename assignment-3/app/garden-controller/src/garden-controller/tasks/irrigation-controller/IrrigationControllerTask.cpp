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
        getMessageBus()->push(MessageType::NOTIFY_IRRIGATOR_CLOSED);
        setState(IrrigationControllerTaskState::CLOSED);
        return;
    }

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

void IrrigationControllerTask::onClosedState() {
    if (this->hasToBeOpened()) {
        this->getMessageBus()->push(MessageType::NOTIFY_IRRIGATOR_OPENED);
        this->setState(IrrigationControllerTaskState::OPEN);
    }
}

void IrrigationControllerTask::onIdleState() {
    if (this->appData->getStatus() == Status::AUTO) {
        this->getMessageBus()->push(MessageType::NOTIFY_IRRIGATOR_OPENED);
        this->setState(IrrigationControllerTaskState::OPEN);
    }
}


// Utils

bool IrrigationControllerTask::hasToBeClosed() {
    if (this->appData->getStatus() == Status::AUTO) {
        long elapsedTimeSinceOpened = millis() - this->openTimestamp;
        return elapsedTimeSinceOpened > this->OPEN_TIME_MILLISECONDS;
    }
    else if (this->appData->getStatus() == Status::MANUAL) {
        return getMessageBus()->isMessagePresent(MessageType::CLOSE_IRRIGATOR);
    }
    else {
        return false;
    }
}

bool IrrigationControllerTask::hasToBeOpened() {
    if (this->appData->getStatus() == Status::AUTO) {
        long elapsedTimeSinceOpened = millis() - this->closeTimestamp;
        return elapsedTimeSinceOpened > this->CLOSED_TIME_MILLISECONDS;
    }
    else if (this->appData->getStatus() == Status::MANUAL) {
        return getMessageBus()->isMessagePresent(MessageType::OPEN_IRRIGATOR);
    }
    else {
        return false;
    }
}
