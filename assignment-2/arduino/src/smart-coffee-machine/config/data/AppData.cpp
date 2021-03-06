#include "AppData.h"

Beverage AppData::getSelectedBeverage() {
    return this->selectedBeverage;
}

String AppData::getSelectedBeverageToString() {
    switch (this->selectedBeverage)
    {
    case COFFEE:
        return "Coffee";
        break;
    case TEA:
        return "Tea";
        break;
    case CHOCOLATE:
        return "Chocolate";
        break;
    default:
        return "";
    };
}

void AppData::setSugarLevel(uint8_t sugarLevel) {
    this->sugarLevel = sugarLevel;
}

uint8_t AppData::getSugarLevel() {
    return this->sugarLevel;
}


uint8_t AppData::getAvailableItemCount(Beverage beverage) {
    return availableItemCount[beverage];
}

bool AppData::consumeItem(Beverage beverage) {
    if (getAvailableItemCount(beverage) == 0) {
        return false;
    }

    availableItemCount[beverage]--;
    return true;
}

bool AppData::selectNextBeverage() {
    switch (this->selectedBeverage)
    {
    case COFFEE:
        this->selectedBeverage = TEA;
        break;
    case TEA:
        this->selectedBeverage = CHOCOLATE;
        break;
    case CHOCOLATE:
        this->selectedBeverage = COFFEE;
        break;
    }
    return getAvailableItemCount(this->selectedBeverage) > 0 ? true : selectNextBeverage();
}

bool AppData::selectPreviousBeverage() {
    if (isRefillNeeded()) {
        return false;
    }

    switch (this->selectedBeverage)
    {
    case COFFEE:
        this->selectedBeverage = CHOCOLATE;
        break;
    case TEA:
        this->selectedBeverage = COFFEE;
        break;
    case CHOCOLATE:
        this->selectedBeverage = TEA;
        break;
    }
    return getAvailableItemCount(this->selectedBeverage) > 0 ? true : selectPreviousBeverage();
}

bool AppData::isRefillNeeded() {
    return getAvailableItemCount(COFFEE) == 0 &&
        getAvailableItemCount(TEA) == 0 &&
        getAvailableItemCount(CHOCOLATE) == 0;
}

void AppData::refill() {
    availableItemCount[COFFEE] = MAX_ITEM_COUNT;
    availableItemCount[TEA] = MAX_ITEM_COUNT;
    availableItemCount[CHOCOLATE] = MAX_ITEM_COUNT;
}

void AppData::setStatus(Status status) {
    this->status = status;
}

Status AppData::getStatus() {
    return this->status;
}

void AppData::increaseSelfCheckPerformed() {
    this->selfCheckPerformedCount++;
}

int AppData::getSelfCheckPerformedCount() {
    return this->selfCheckPerformedCount;
}
