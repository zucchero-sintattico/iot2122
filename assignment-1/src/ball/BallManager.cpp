#include "BallManager.h"

#include <Arduino.h>

BallManager::BallManager(uint8_t ledPins[4]) {
    memcpy(this->ledPins, ledPins, sizeof(this->ledPins));
    this->actualLedIndexPosition = -1;
}

void BallManager::setup() {
    for (int i = 0; i < 4; i++) {
        pinMode(this->ledPins[i], OUTPUT);
    }
}

void BallManager::start() {
    this->actualLedIndexPosition = -1;
    this->prevLedIndexPosition = -1;
    this->directionalIncrement = 1;
}

void BallManager::stop() {
    this->actualLedIndexPosition = -1;
    for (int i = 0; i < 4; i++) {
        digitalWrite(this->ledPins[i], LOW);
    }
}

void BallManager::nextBall() {
    if (this->isDirectionChangeNeeded()) {
        this->changeDirection();
    }
    this->incrementPosition();
    this->turnOffPreviousLedIfPresent();
    this->turnOnActualLed();
}

uint8_t BallManager::getCurrentBallIndex() {
    return this->actualLedIndexPosition;
}

bool BallManager::isDirectionChangeNeeded() {
    return (this->actualLedIndexPosition == 3 && this->directionalIncrement == 1) || (this->actualLedIndexPosition == 0 && this->directionalIncrement == -1);
}

void BallManager::changeDirection() {
    this->directionalIncrement *= -1;
}

void BallManager::incrementPosition() {
    this->prevLedIndexPosition = this->actualLedIndexPosition;
    this->actualLedIndexPosition += this->directionalIncrement;
}

void BallManager::turnOffPreviousLedIfPresent() {
    if (this->prevLedIndexPosition != -1) {
        digitalWrite(this->ledPins[this->prevLedIndexPosition], LOW);
    }
}

void BallManager::turnOnActualLed() {
    digitalWrite(this->ledPins[this->actualLedIndexPosition], HIGH);
}