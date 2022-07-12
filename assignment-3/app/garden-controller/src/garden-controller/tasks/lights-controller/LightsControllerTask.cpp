#include "LightsControllerTask.h"

void LightsControllerTask::init() {
    this->digitalLed1->setup();
    this->digitalLed2->setup();
    this->analogLed1->setup();
    this->analogLed2->setup();
}

void LightsControllerTask::computeRead() {}

void LightsControllerTask::tick() {
    switch (this->getState())
    {
    case LightsControllerTaskState::IDLE:
        this->onIdleState();
        break;
    case LightsControllerTaskState::WORKING:
        this->onWorkingState();
        break;
    }
}


void LightsControllerTask::onIdleState() {
    if (this->appData->getStatus() == Status::AUTO || this->appData->getStatus() == Status::MANUAL) {
        this->setState(LightsControllerTaskState::WORKING);
    }
}

void LightsControllerTask::onWorkingState() {
    if (this->appData->getStatus() == Status::ALARM) {
        this->setState(LightsControllerTaskState::IDLE);
    }
    else {
        this->digitalLed1->setActive(this->appData->isDigitalLed1Active());
        this->digitalLed2->setActive(this->appData->isDigitalLed2Active());
        this->analogLed1->setValue(map(this->appData->getAnalogLed1Value(), 0, 4, 0, 255));
        this->analogLed2->setValue(map(this->appData->getAnalogLed2Value(), 0, 4, 0, 255));
    }
}
