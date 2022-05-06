#include "BeverageSelectorTask.h"

void BeverageSelectorTask::init() {
    this->buttonUp->setup();
    this->buttonDown->setup();
    this->buttonMake->setup();
    this->sugarManager->setup();
}

void BeverageSelectorTask::computeRead() {
    this->buttonUp->computeRead();
    this->buttonDown->computeRead();
    this->buttonMake->computeRead();
    this->sugarManager->computeRead();
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
        this->setState(BeverageSelectorTaskState::ASSISTANCE);
        return;
    }

    this->display->printReadyMessage();

    if (isAnyButtonPressed()) {
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::SELECTING);
        return;
    }
}

void BeverageSelectorTask::onSelectingState() {

    this->appData->setSugarLevel(this->sugarManager->getPercentage());

    if (buttonUp->isPressed()) {
        this->appData->selectNextBeverage();
    }

    if (buttonDown->isPressed()) {
        this->appData->selectPreviousBeverage();
    }

    if (buttonMake->isPressed()) {
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_MAKER_TASK);
        this->setState(BeverageSelectorTaskState::IDLE);
    }

    this->display->printSelectingInfoMessage();
}

void BeverageSelectorTask::onAssistanceState() {

    this->display->printSelectingAssistanceMessage();

    if (this->getMessageBus()->isMessagePresent(MessageType::REFILL)) {
        this->getMessageBus()->removeMessage(MessageType::REFILL);
        this->appData->refill();
        this->setState(BeverageSelectorTaskState::READY);
    }
}