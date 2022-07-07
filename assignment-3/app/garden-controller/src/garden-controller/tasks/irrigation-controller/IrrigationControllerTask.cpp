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
    switch (getState())
    {
    case IrrigationControllerTaskState::CLOSED:
        return false;
    case IrrigationControllerTaskState::IDLE:
        return false;
    case IrrigationControllerTaskState::OPEN:
        switch (appData->getStatus())
        {
        case Status::ALARM:
            return false;
        case Status::AUTO:
            long elapsedTimeSinceOpened = millis() - this->openTimestamp;
            return elapsedTimeSinceOpened > this->OPEN_TIME_MILLISECONDS;
        case Status::MANUAL:
            bool isThereCommand = getMessageBus()->isMessagePresent(MessageType::NOTIFY_CLOSE_IRRIGATOR);
            if (isThereCommand) {
                getMessageBus()->removeMessage(MessageType::NOTIFY_CLOSE_IRRIGATOR);
            }
            return isThereCommand;
        }
    }
}

bool IrrigationControllerTask::hasToBeOpened() {
    switch (getState())
    {
    case IrrigationControllerTaskState::IDLE:
        return this->appData->getStatus() == Status::AUTO;
    case IrrigationControllerTaskState::OPEN:
        return false;
    case IrrigationControllerTaskState::CLOSED:
        switch (appData->getStatus())
        {
        case Status::AUTO:
            long elapsedTimeSinceOpened = millis() - this->closeTimestamp;
            return elapsedTimeSinceOpened > this->CLOSED_TIME_MILLISECONDS;
        case Status::MANUAL:
            bool isThereCommand = getMessageBus()->isMessagePresent(MessageType::NOTIFY_OPEN_IRRIGATOR);
            if (isThereCommand) {
                getMessageBus()->removeMessage(MessageType::NOTIFY_OPEN_IRRIGATOR);
            }
            return isThereCommand;
        case Status::ALARM:
            return false;
        }
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
    this->appData->setIrrigatorOpen(true);
    this->openTimestamp = millis();
    this->setState(IrrigationControllerTaskState::OPEN);
}

void IrrigationControllerTask::changeStateToClosed() {
    this->appData->setIrrigatorOpen(false);
    closeTimestamp = millis();
    setState(IrrigationControllerTaskState::CLOSED);
}