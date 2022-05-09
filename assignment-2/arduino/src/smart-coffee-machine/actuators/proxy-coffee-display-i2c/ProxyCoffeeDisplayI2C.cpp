#include "ProxyCoffeeDisplayI2C.h"

ProxyCoffeeDisplayI2C* ProxyCoffeeDisplayI2C::_instance = nullptr;
ProxyCoffeeDisplayI2C* ProxyCoffeeDisplayI2C::getInstance() {
    if (_instance == nullptr) {
        _instance = new ProxyCoffeeDisplayI2C();
    }
    return _instance;
}

void ProxyCoffeeDisplayI2C::printWelcomeMessage() {
    if (this->lastMessage != BOOT) {
        this->lastMessage = BOOT;
        CoffeeDisplayI2C::printWelcomeMessage();
    }
}

void ProxyCoffeeDisplayI2C::printReadyMessage() {
    if (this->lastMessage != READY) {
        this->lastMessage = READY;
        CoffeeDisplayI2C::printReadyMessage();
    }
}

void ProxyCoffeeDisplayI2C::setSelectingInfoScreen() {
    if (this->lastMessage != SET_SELECTING_INFO) {
        this->lastMessage = SET_SELECTING_INFO;
        CoffeeDisplayI2C::setSelectingInfoScreen();
    }
}

void ProxyCoffeeDisplayI2C::updateSelectingInfoScreen(AppData* appData) {
    if (appData->getSelectedBeverage() != this->lastBeverage || appData->getSugarLevel() != this->lastSugarLevel) {
        this->lastBeverage = appData->getSelectedBeverage();
        this->lastSugarLevel = appData->getSugarLevel();
        CoffeeDisplayI2C::updateSelectingInfoScreen(appData);
    }
}

void ProxyCoffeeDisplayI2C::printAssistanceMessage() {
    if (this->lastMessage != SELECTING_ASSISTANCE) {
        this->lastMessage = SELECTING_ASSISTANCE;
        CoffeeDisplayI2C::printAssistanceMessage();
    }
}

void ProxyCoffeeDisplayI2C::setMakingInfoScreen(AppData* appData) {
    if (this->lastMessage != SET_MAKING_INFO) {
        this->lastMessage = SET_MAKING_INFO;
        CoffeeDisplayI2C::setMakingInfoScreen(appData);
    }
}

void ProxyCoffeeDisplayI2C::updateMakingInfo(int percentage) {
    if (this->lastPercentage != percentage) {
        this->lastPercentage = percentage;
        CoffeeDisplayI2C::updateMakingInfo(percentage);
    }
}

void ProxyCoffeeDisplayI2C::printWaitingForRetireMessage() {
    if (this->lastMessage != WAITING_FOR_RETIRE) {
        this->lastMessage = WAITING_FOR_RETIRE;
        CoffeeDisplayI2C::printWaitingForRetireMessage();
    }
}