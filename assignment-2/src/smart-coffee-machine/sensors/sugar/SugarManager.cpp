#include "SugarManager.h"

SugarManager::SugarManager(int pin) : PotentiometerManager(pin) {}

double SugarManager::getPercentage() {
    return map(this->getValue(), 0, 1023, 0, 100);
}