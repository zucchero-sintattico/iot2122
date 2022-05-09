#include "SelfCheckTask.h"
#define MAX_TEMPERATURE 24
#define MIN_TEMPERATURE 17
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
    if (this->elapsedTime == MAX_PERIOD) {
        this->elapsedTime = 0;
        this->setState(SelfCheckTaskState::MECHANIC_CHECK);
    }
}

void SelfCheckTask::onMechanicCheckState() {
    this->angle += this->increment;
    this->motor->rotateTo(this->angle);
    if (this->angle == MAX_ANGLE) {
        this->increment = -1;
    }
    else if (this->angle == MIN_ANGLE) {
        this->increment = 1;
        this->setState(SelfCheckTaskState::TEMPERATURE_CHECK);
    }
}

void SelfCheckTask::onTemperatureCheckState() {
    uint8_t temperature = this->thermometerManager->getTemperature();
    if (temperature >= MIN_TEMPERATURE && temperature <= MAX_TEMPERATURE) {
        this->setState(SelfCheckTaskState::IDLE);
    }
    else {
        this->setState(SelfCheckTaskState::ASSISTANCE);
    }
}

void SelfCheckTask::onAssistanceState() {
    this->display->printAssistanceMessage();
    if (this->getMessageBus()->isMessagePresent(MessageType::RECOVER)) {
        this->getMessageBus()->removeMessage(MessageType::RECOVER);
        this->setState(SelfCheckTaskState::IDLE);
    }
}