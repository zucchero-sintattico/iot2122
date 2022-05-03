#include "PresenceTask.h"

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
    // TODO: implement
}

void PresenceTask::onNooneState() {
    if (this->pirManager->isSomeoneDetected()) {
        this->setState(PresenceTaskState::SOMEONE);
    } else {
        this->elapsedTickNooneDetected++;
        if (this->elapsedTickNooneDetected >= this->tickToSleep) {
            this->setState(PresenceTaskState::SLEEP);
        }
    }
}

void PresenceTask::onSomeoneState() {
    this->elapsedTickNooneDetected = 0;
    if (!this->pirManager->isSomeoneDetected()) {
        this->setState(PresenceTaskState::NOONE);
    }
}

void PresenceTask::onSleepState() {
    // TODO: implement
}

