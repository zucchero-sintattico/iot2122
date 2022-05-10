#include "BeverageSelectorTask.h"

void BeverageSelectorTask::init() {
    this->buttonUp->setup();
    this->buttonDown->setup();
    this->buttonMake->setup();
    this->potentiometer->setup();
}

void BeverageSelectorTask::computeRead() {
    this->buttonUp->computeRead();
    this->buttonDown->computeRead();
    this->buttonMake->computeRead();
    this->potentiometer->computeRead();
}

void BeverageSelectorTask::tick() {
    switch (this->getState())
    {
    case BeverageSelectorTaskState::IDLE:
        this->onIdleState();
        break;
    case BeverageSelectorTaskState::READY:
        this->onReadyState();
        break;
    case BeverageSelectorTaskState::SELECTING:
        this->onSelectingState();
        break;
    case BeverageSelectorTaskState::ASSISTANCE:
        this->onAssistanceState();
        break;
    }
}

void BeverageSelectorTask::onIdleState() {
    if (this->getMessageBus()->isMessagePresent(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK)) {
        this->getMessageBus()->removeMessage(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK);
        this->getMessageBus()->push(MessageType::ACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::READY);
    }
}


bool BeverageSelectorTask::isAnyButtonPressed() {
    return this->buttonUp->isPressed() || this->buttonDown->isPressed() || this->buttonMake->isPressed();
}

void BeverageSelectorTask::onReadyState() {
    if (appData->isRefillNeeded()) {
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->appData->setStatus(Status::ASSISTANCE);
        this->setState(BeverageSelectorTaskState::ASSISTANCE);
        return;
    }

    if (this->getMessageBus()->isMessagePresent(MessageType::SELF_CHECK_IN_PROGRESS) || this->appData->getStatus() == Status::ASSISTANCE) {
        return;
    }

    this->display->printReadyMessage();

    if (isAnyButtonPressed()) {
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::SELECTING);
        this->display->setSelectingInfoScreen();
        if (appData->getAvailableItemCount(appData->getSelectedBeverage()) == 0) {
            this->appData->selectNextBeverage();
        }
        this->lastIteractionTime = millis();
        return;
    }
}

bool BeverageSelectorTask::isSelectingTimeElapsed() {
    return millis() - this->lastIteractionTime > MAX_SELECTING_TIME;
}

void BeverageSelectorTask::onSelectingState() {

    if (this->appData->getSugarLevel() != this->potentiometer->getPercentage()) {
        this->lastIteractionTime = millis();
        this->appData->setSugarLevel(this->potentiometer->getPercentage());
    }

    if (buttonUp->isPressed()) {
        this->lastIteractionTime = millis();
        this->appData->selectNextBeverage();
    }

    if (buttonDown->isPressed()) {
        this->lastIteractionTime = millis();
        this->appData->selectPreviousBeverage();
    }

    this->display->updateSelectingInfoScreen(this->appData);

    if (isSelectingTimeElapsed()) {
        this->getMessageBus()->push(MessageType::ACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::READY);
        return;
    }

    if (buttonMake->isPressed()) {
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_MAKER_TASK);
        this->setState(BeverageSelectorTaskState::IDLE);
    }

}

void BeverageSelectorTask::onAssistanceState() {
    this->display->printAssistanceMessage();
    if (!this->appData->isRefillNeeded()) {
        this->appData->setStatus(Status::IDLE);
        this->setState(BeverageSelectorTaskState::READY);
    }
}