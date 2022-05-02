#include "AppData.h"

bool AppData::isRefillNeeded() {
    return availableCoffee == 0 && availableTea == 0 && availableChocolate == 0;
}

int AppData::getAvailableCoffee() {
    return this->availableCoffee;
}

int AppData::getAvailableTea() {
    return this->availableTea;
}

int AppData::getAvailableChocolate() {
    return this->availableChocolate;
}

bool AppData::consumeCoffee() {
    if (this->availableCoffee > 0) {
        this->availableCoffee--;
        return true;
    }
    return false;
}

bool AppData::consumeTea() {
    if (this->availableTea > 0) {
        this->availableTea--;
        return true;
    }
    return false;
}

bool AppData::consumeChocolate() {
    if (this->availableChocolate > 0) {
        this->availableChocolate--;
        return true;
    }
    return false;
}

void AppData::refill() {
    this->availableCoffee = MAX_AVAILABLE_COFFEE;
    this->availableTea = MAX_AVAILABLE_TEA;
    this->availableChocolate = MAX_AVAILABLE_CHOCOLATE;
}