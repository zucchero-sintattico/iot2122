#include "BeverageSelectorTask.h"

void BeverageSelectorTask::init() {
    this->buttonUpManager->setup();
    this->buttonDownManager->setup();
    this->buttonMakeManager->setup();
    this->sugarManager->setup();
}

void BeverageSelectorTask::computeRead() {
    this->buttonUpManager->computeRead();
    this->buttonDownManager->computeRead();
    this->buttonMakeManager->computeRead();
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
    return this->buttonUpManager->isPressed() || this->buttonDownManager->isPressed() || this->buttonMakeManager->isPressed();
}

void BeverageSelectorTask::onReadyState() {
    if (this->appData->isRefillNeeded()) {
        this->setState(BeverageSelectorTaskState::ASSISTANCE);
        return;
    }

    // Print READY to display

    if (this->isAnyButtonPressed()) {
        this->getMessageBus()->push(MessageType::DEACTIVATE_PRESENCE_TASK);
        this->setState(BeverageSelectorTaskState::SELECTING);
    }
}

void BeverageSelectorTask::onSelectingState() {
    Serial.println("BeverageSelectorTask::onSelectingState");
}

void BeverageSelectorTask::onAssistanceState() {

    // Display ASSISTANCE REQUIRED message

    if (this->getMessageBus()->isMessagePresent(MessageType::REFILL)) {
        this->getMessageBus()->removeMessage(MessageType::REFILL);
        this->appData->refill();
        this->setState(BeverageSelectorTaskState::READY);
    }
}