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
    Serial.println("BeverageSelectorTask::onIdleState");
}

void BeverageSelectorTask::onReadyState() {
    Serial.println("BeverageSelectorTask::onReadyState");
}

void BeverageSelectorTask::onSelectingState() {
    Serial.println("BeverageSelectorTask::onSelectingState");
}

void BeverageSelectorTask::onAssistanceState() {
    Serial.println("BeverageSelectorTask::onAssistanceState");
}