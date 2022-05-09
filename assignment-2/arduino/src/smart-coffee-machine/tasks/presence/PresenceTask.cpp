#include "PresenceTask.h"

#include <EnableInterrupt.h>
#include <avr/sleep.h>

void PresenceTask::init() {
    this->pirManager->setup();
}

void PresenceTask::computeRead() {
    this->pirManager->computeRead();
}

void PresenceTask::tick() {
    switch (this->getState())
    {
    case PresenceTaskState::IDLE:
        this->onIdleState();
        break;
    case PresenceTaskState::NOONE:
        this->onNooneState();
        break;
    case PresenceTaskState::SOMEONE:
        this->onSomeoneState();
        break;
    case PresenceTaskState::SLEEP:
        this->onSleepState();
        break;
    }
}

void PresenceTask::onIdleState() {
    if (this->getMessageBus()->isMessagePresent(MessageType::ACTIVATE_PRESENCE_TASK)) {
        this->getMessageBus()->removeMessage(MessageType::ACTIVATE_PRESENCE_TASK);
        if (this->pirManager->isSomeoneDetected()) {
            this->setState(PresenceTaskState::SOMEONE);
        }
        else {
            this->setState(PresenceTaskState::NOONE);
        }
    }
}

void PresenceTask::onNooneState() {
    if (this->needIdleState()) {
        this->setState(PresenceTaskState::IDLE);
        return;
    }

    if (this->pirManager->isSomeoneDetected()) {
        this->setState(PresenceTaskState::SOMEONE);
    }
    else {
        this->elapsedTickNooneDetected++;
        if (this->elapsedTickNooneDetected >= this->tickToSleep) {
            this->setState(PresenceTaskState::SLEEP);
        }
    }
}

void PresenceTask::onSomeoneState() {
    this->elapsedTickNooneDetected = 0;

    if (this->needIdleState()) {
        this->setState(PresenceTaskState::IDLE);
        return;
    }

    if (!this->pirManager->isSomeoneDetected()) {
        this->setState(PresenceTaskState::NOONE);
    }
}

bool PresenceTask::needIdleState() {
    if (this->getMessageBus()->isMessagePresent(MessageType::DEACTIVATE_PRESENCE_TASK)) {
        this->getMessageBus()->removeMessage(MessageType::DEACTIVATE_PRESENCE_TASK);
        return true;
    }
    return false;
}

void emptyFunc() {}

void PresenceTask::onSleepState() {
    enableInterrupt(this->pirManager->getPin(), &emptyFunc, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    disableInterrupt(this->pirManager->getPin());
    this->setState(PresenceTaskState::SOMEONE);
}
