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
        this->onIdleState();
        break;
    case PresenceTaskState::SOMEONE:
        this->onSomeoneState();
        break;
    case PresenceTaskState::SLEEP:
        this->onSleepState();
        break;
    }
}
#include <time.h>
unsigned long t0 = millis();
void PresenceTask::onIdleState() {
    /*Serial.println(String(millis() - t0));
    t0 = millis();*/
}

void PresenceTask::onNooneState() {
    // TODO: implement
}

void PresenceTask::onSomeoneState() {
    // TODO: implement
}

void PresenceTask::onSleepState() {
    // TODO: implement
}

