#include "IrrigationControllerTask.h"

void IrrigationControllerTask::init() {
    this->motor->setup();
}

void IrrigationControllerTask::computeRead() {

}

void IrrigationControllerTask::tick() {
    switch (this->getState())
    {
    case IrrigationControllerTaskState::READY:
        this->onReadyState();
        break;
    case IrrigationControllerTaskState::OPEN:
        this->onOpenState();
        break;
    case IrrigationControllerTaskState::CLOSED:
        this->onClosedState();
        break;
    }
}

void IrrigationControllerTask::onReadyState() {

    switch (appData->getStatus()) {
    case ALARM:
        return;
    case AUTO:
    case MANUAL:
        if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_OPEN_IRRIGATOR)) {
            getMessageBus()->removeMessage(MessageType::NOTIFY_OPEN_IRRIGATOR);
            changeStateToOpen();
        }
    }
}

void IrrigationControllerTask::onOpenState() {

    switch (appData->getStatus())
    {
    case ALARM:
        changeStateToClosed();
        return;
    case MANUAL:
        if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_CLOSE_IRRIGATOR)) {
            getMessageBus()->removeMessage(MessageType::NOTIFY_CLOSE_IRRIGATOR);
            changeStateToClosed();
        }
        break;
    case AUTO:
        long elapsedTimeSinceOpened = millis() - this->openTimestamp;
        if (elapsedTimeSinceOpened > OPEN_TIME_MILLISECONDS) {
            changeStateToClosed();
            return;
        }
    }

    rotate();
}

void IrrigationControllerTask::onClosedState() {
    if (getMessageBus()->isMessagePresent(MessageType::NOTIFY_OPEN_IRRIGATOR)) {
        getMessageBus()->removeMessage(MessageType::NOTIFY_OPEN_IRRIGATOR);
        changeStateToOpen();
        return;
    }
    long elapsedTimeSinceOpened = millis() - this->closeTimestamp;
    if (elapsedTimeSinceOpened > this->CLOSED_TIME_MILLISECONDS) {
        this->appData->setIrrigatorStatus(IrrigatorStatus::READY);
        setState(IrrigationControllerTaskState::READY);
    }

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
    this->appData->setIrrigatorStatus(IrrigatorStatus::OPEN);
    this->openTimestamp = millis();
    this->setState(IrrigationControllerTaskState::OPEN);
}

void IrrigationControllerTask::changeStateToClosed() {
    this->appData->setIrrigatorStatus(IrrigatorStatus::CLOSED);
    this->closeTimestamp = millis();
    setState(IrrigationControllerTaskState::CLOSED);
}