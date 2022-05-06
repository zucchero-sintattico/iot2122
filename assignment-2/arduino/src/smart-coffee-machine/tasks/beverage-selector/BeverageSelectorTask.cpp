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
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::ASSISTANCE);
        return;
    }

    this->display->printReadyMessage();

    if (isAnyButtonPressed()) {
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::SELECTING);
        this->lastIteractionTime = millis();
        return;
    }
}

bool BeverageSelectorTask::isSelectingTimeElapsed() {
    return millis() - this->lastIteractionTime > MAX_SELECTING_TIME;
}

void BeverageSelectorTask::onSelectingState() {

    if (this->appData->getSugarLevel() != this->sugarManager->getPercentage()) {
        this->lastIteractionTime = millis();
        this->appData->setSugarLevel(this->sugarManager->getPercentage());
    }

    if (buttonUp->isPressed()) {
        this->lastIteractionTime = millis();
        this->appData->selectNextBeverage();
    }

    if (buttonDown->isPressed()) {
        this->lastIteractionTime = millis();
        this->appData->selectPreviousBeverage();
    }

    this->display->printSelectingInfoMessage(this->appData);

    if (isSelectingTimeElapsed()) {
        this->getMessageBus()->push(MessageType::ACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::READY);
        Serial.println("Selecting time elapsed");
        return;
    }

    if (buttonMake->isPressed()) {
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_MAKER_TASK);
        this->setState(BeverageSelectorTaskState::IDLE);
    }

}

void BeverageSelectorTask::onAssistanceState() {
    this->display->printSelectingAssistanceMessage();

    if (this->getMessageBus()->isMessagePresent(MessageType::REFILL)) {
        this->getMessageBus()->removeMessage(MessageType::REFILL);
        this->appData->refill();
        this->setState(BeverageSelectorTaskState::READY);
    }
}