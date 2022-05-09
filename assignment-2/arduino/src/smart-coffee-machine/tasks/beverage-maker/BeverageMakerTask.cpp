#include "BeverageMakerTask.h"

void BeverageMakerTask::init() {
    this->sonar->setup();
    this->motor->setup();
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
        this->display->setMakingInfoScreen(this->appData);
        this->setState(BeverageMakerTaskState::MAKING);
    }
}

void BeverageMakerTask::onMakingState() {
    this->progressPercentage += INCREMENT_PERCENTAGE;
    this->motor->rotateTo(map(this->progressPercentage, 0, 100, 0, 180));
    this->display->updateMakingInfo(this->progressPercentage);
    if (this->progressPercentage == 100) {
        this->appData->consumeItem(this->appData->getSelectedBeverage());
        this->elapsedWaitingTime = 0;
        this->setState(BeverageMakerTaskState::WAITING);
    }

}

void BeverageMakerTask::onWaitingState() {
    this->elapsedWaitingTime += this->getPeriod();
    this->display->printWaitingForRetireMessage();
    if (this->sonar->getDistanceInCM() > MAX_DISTANCE_IN_CM || this->elapsedWaitingTime > MAX_WAITING_TIME_IN_MS) {
        this->progressPercentage = 0;
        this->motor->rotateTo(0);
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK);
        this->setState(BeverageMakerTaskState::IDLE);
    }
}