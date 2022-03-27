#include "ButtonsManager.h"

#define LIBCALL_ENABLEINTERRUPT
#include <Arduino.h>
#include <EnableInterrupt.h>

ButtonsManager* ButtonsManager::currentManager;

bool ButtonsManager::isBouncingInterrupt() {
    static unsigned long BOUNCING_LIMIT_MILLISECONDS = 100;
    static unsigned long prevTimestamp = 0;
    unsigned long currentTimestamp = millis();
    unsigned long result = currentTimestamp - prevTimestamp < BOUNCING_LIMIT_MILLISECONDS;
    prevTimestamp = currentTimestamp;
    return result;
}

void ButtonsManager::handleInterrupt() {
    if (!ButtonsManager::isBouncingInterrupt()) {
        for (int i = 0; i < 4; i++) {
            if (digitalRead(ButtonsManager::currentManager->buttonPins[i]) == HIGH) {
                ButtonsManager::currentManager->setButtonPressed(i);
            }
        }
    }
}

void ButtonsManager::attachCurrentManager(ButtonsManager* manager) {
    ButtonsManager::currentManager = manager;
}

ButtonsManager::ButtonsManager(uint8_t buttonPins[4]) {
    memcpy(this->buttonPins, buttonPins, sizeof(this->buttonPins));
    for (int i = 0; i < 4; i++) {
        this->buttonStates[i] = false;
    }
}

void ButtonsManager::setup() {
    ButtonsManager::attachCurrentManager(this);
    for (int i = 0; i < 4; i++) {
        pinMode(this->buttonPins[i], INPUT);
    }
}

void ButtonsManager::start() {
    for (int i = 0; i < 4; i++) {
        enableInterrupt(this->buttonPins[i], &ButtonsManager::handleInterrupt, RISING);
    }
    this->releasePressedButton();
}

void ButtonsManager::stop() {
    for (int i = 0; i < 4; i++) {
        disableInterrupt(this->buttonPins[i]);
    }
}

void ButtonsManager::setButtonPressed(uint8_t index) {
    this->buttonStates[index] = true;
}


bool ButtonsManager::hasAnyButtonBeenPressed() {
    for (int i = 0; i < 4; i++) {
        if (this->buttonStates[i]) {
            return true;
        }
    }
    return false;
}

uint8_t ButtonsManager::getPressedButtonIndex() {
    for (int i = 0; i < 4; i++) {
        if (this->buttonStates[i]) {
            return i;
        }
    }
    return -1;
}

void ButtonsManager::releasePressedButton() {
    noInterrupts();
    for (int i = 0; i < 4; i++) {
        noInterrupts();
        this->buttonStates[i] = false;
        interrupts();
    }
}

