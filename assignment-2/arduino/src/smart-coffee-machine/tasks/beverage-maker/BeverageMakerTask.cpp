#include "BeverageMakerTask.h"

void BeverageMakerTask::init() {
    this->sonar->setup();
    // this->servo->setup();
}

void BeverageMakerTask::computeRead() {
    if (this->getState() == BeverageMakerTaskState::WAITING) {
        this->sonar->computeRead();
    }
}

void BeverageMakerTask::tick() {
    switch (this->getState())
    {
    case BeverageMakerTaskState::IDLE:
        this->onIdleState();
        break;
    case BeverageMakerTaskState::MAKING:
        this->onMakingState();
        break;
    case BeverageMakerTaskState::WAITING:
        this->onWaitingState();
        break;
    }
}


void BeverageMakerTask::onIdleState() {
    if (this->getMessageBus()->isMessagePresent(MessageType::ACTIVATE_BEVERAGE_MAKER_TASK)) {
        this->getMessageBus()->removeMessage(MessageType::ACTIVATE_BEVERAGE_MAKER_TASK);
        this->progressPercentage = 0;
        this->setState(BeverageMakerTaskState::MAKING);
    }
}

void BeverageMakerTask::onMakingState() {
    this->progressPercentage += INCREMENT_PERCENTAGE;
    this->display->printMakingInfo(this->appData, this->progressPercentage);
    if (this->progressPercentage == 100) {
        this->setState(BeverageMakerTaskState::WAITING);
    }

}

void BeverageMakerTask::onWaitingState() {
    this->display->printWaitingForRetireMessage();
    if (this->sonar->getDistanceInCM() > MAX_DISTANCE_IN_CM) {
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK);
        this->setState(BeverageMakerTaskState::IDLE);
    }
}