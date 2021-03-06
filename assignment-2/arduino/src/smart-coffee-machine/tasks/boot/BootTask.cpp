#include "./BootTask.h"

void BootTask::init() {}

void BootTask::computeRead() {}

void BootTask::tick() {
    switch (this->getState())
    {
    case BootTaskState::BOOT:
        this->onBootState();
        break;
    case BootTaskState::IDLE:
        this->onIdleState();
        break;
    }
}

void BootTask::onBootState() {
    this->coffeeDisplay->printWelcomeMessage();
    this->elapsed += this->_period;
    if (this->elapsed >= this->duration) {
        this->getMessageBus()->push(MessageType::ACTIVATE_BEVERAGE_SELECTOR_TASK);
        this->elapsed = 0;
        this->setState(BootTaskState::IDLE);
    }
}

void BootTask::onIdleState() {}
