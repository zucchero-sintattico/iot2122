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

void emptyFunc() {}

void PresenceTask::onSleepState() {
    enableInterrupt(this->pirPin, &emptyFunc, RISING);
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    sleep_mode();
    sleep_disable();
    disableInterrupt(this->pirPin);
    this->setState(PresenceTaskState::SOMEONE);
}
