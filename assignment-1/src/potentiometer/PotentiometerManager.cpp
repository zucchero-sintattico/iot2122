#include "PotentiometerManager.h"

#include <Arduino.h>

PotentiometerManager::PotentiometerManager(uint8_t potentiometerPin, uint8_t difficultyLevels = 8) {
    this->potentiometerPin = potentiometerPin;
    this->difficultyLevels = difficultyLevels;
}

void PotentiometerManager::setup() {
    pinMode(this->potentiometerPin, INPUT);
}

int PotentiometerManager::readPotentiometer() {
    return analogRead(this->potentiometerPin);
}

uint8_t PotentiometerManager::getDifficultyFactor() {
    return map(this->readPotentiometer(), 0, 1024, 0, this->difficultyLevels) + 1;
}