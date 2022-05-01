#include "SugarManager.h"

SugarManager::SugarManager(int pin) : PotentiometerManager(pin) {}

int SugarManager::getPercentage() {
    return map(this->getValue(), 0, 1023, 0, 100);
}