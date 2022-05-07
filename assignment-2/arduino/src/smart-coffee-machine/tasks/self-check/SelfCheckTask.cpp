#include "SelfCheckTask.h"

void SelfCheckTask::init() {
    this->thermometerManager->setup();
    this->servoManager->setup();
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
    // TODO: implement
}

void SelfCheckTask::onMechanicCheckState() {
    // TODO: implement
}

void SelfCheckTask::onTemperatureCheckState() {
    // TODO: implement
}

void SelfCheckTask::onAssistanceState() {
    // TODO: implement
}