#include "SelfCheckTask.h"
#define MAX_TEMPERATURE 30
#define MIN_TEMPERATURE 20
#define MIN_ANGLE 0
#define MAX_ANGLE 180


void SelfCheckTask::init() {
    this->thermometerManager->setup();
    this->motor->setup();
}

void SelfCheckTask::computeRead() {
    if (this->getState() == SelfCheckTaskState::TEMPERATURE_CHECK) {
        this->thermometerManager->computeRead();
    }
}

void SelfCheckTask::tick() {
    switch (this->getState()) {
    case SelfCheckTaskState::IDLE:
        onIdleState();
        break;
    case SelfCheckTaskState::MECHANIC_CHECK:
        onMechanicCheckState();
        break;
    case SelfCheckTaskState::TEMPERATURE_CHECK:
        onTemperatureCheckState();
        break;
    case SelfCheckTaskState::ASSISTANCE:
        onAssistanceState();
        break;
    }
}

void SelfCheckTask::onIdleState() {
    this->elapsedTime += this->getPeriod();
    if (this->elapsedTime >= WAITING_TIME && this->appData->getStatus() == Status::IDLE) {
        this->elapsedTime = 0;
        this->display->setMechanicCheckInfoScreen();
        this->appData->setStatus(Status::WORKING);
        this->getMessageBus()->push(MessageType::SELF_CHECK_IN_PROGRESS);
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(SelfCheckTaskState::MECHANIC_CHECK);
    }
}

void SelfCheckTask::onMechanicCheckState() {
    this->totalRotation += incrementFactor;
    this->angle += this->increment;
    this->motor->rotateTo(this->angle);
    this->display->updateMechanicCheckInfo(map(this->totalRotation, 0, 360, 0, 100));
    if (this->angle == MAX_ANGLE) {
        this->increment = -this->increment;
    }
    else if (this->angle == MIN_ANGLE) {
        this->increment = -this->increment;
        this->totalRotation = 0;
        this->setState(SelfCheckTaskState::TEMPERATURE_CHECK);
    }
}

void SelfCheckTask::onTemperatureCheckState() {
    this->appData->increaseSelfCheckPerformed();
    this->getMessageBus()->removeMessage(MessageType::SELF_CHECK_IN_PROGRESS);
    uint8_t temperature = this->thermometerManager->getTemperature();
    Serial.println("TEMPERATURE = " + String(temperature));
    if (temperature >= MIN_TEMPERATURE && temperature <= MAX_TEMPERATURE) {
        this->appData->setStatus(Status::IDLE);
        this->getMessageBus()->push(MessageType::ACTIVATE_PRESENCE_TASK);
        this->setState(SelfCheckTaskState::IDLE);
    }
    else {
        this->appData->setStatus(Status::ASSISTANCE);
        this->setState(SelfCheckTaskState::ASSISTANCE);
    }
}

void SelfCheckTask::onAssistanceState() {
    this->display->printAssistanceMessage();
    if (this->getMessageBus()->isMessagePresent(MessageType::RECOVER)) {
        this->getMessageBus()->removeMessage(MessageType::RECOVER);
        this->appData->setStatus(Status::IDLE);
        this->getMessageBus()->push(MessageType::ACTIVATE_PRESENCE_TASK);
        this->setState(SelfCheckTaskState::IDLE);
    }
}