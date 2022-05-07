#include "ProxyCoffeeDisplayI2C.h"

ProxyCoffeeDisplayI2C* ProxyCoffeeDisplayI2C::_instance = nullptr;
ProxyCoffeeDisplayI2C* ProxyCoffeeDisplayI2C::getInstance() {
    if (_instance == nullptr) {
        _instance = new ProxyCoffeeDisplayI2C();
    }
    return _instance;
}

void ProxyCoffeeDisplayI2C::printBootMessage() {
    if (this->lastMessage != BOOT) {
        this->lastMessage = BOOT;
        CoffeeDisplayI2C::printBootMessage();
    }
}

void ProxyCoffeeDisplayI2C::printReadyMessage() {
    if (this->lastMessage != READY) {
        this->lastMessage = READY;
        CoffeeDisplayI2C::printReadyMessage();
    }
}

void ProxyCoffeeDisplayI2C::printSelectingInfoMessage(AppData* appData) {
    CoffeeDisplayI2C::printSelectingInfoMessage(appData);
}

void ProxyCoffeeDisplayI2C::printAssistanceMessage() {
    if (this->lastMessage != SELECTING_ASSISTANCE) {
        this->lastMessage = SELECTING_ASSISTANCE;
        CoffeeDisplayI2C::printAssistanceMessage();
    }
}

void ProxyCoffeeDisplayI2C::printMakingInfo(AppData* appData, int percentage) {
    CoffeeDisplayI2C::printMakingInfo(appData, percentage);
}

void ProxyCoffeeDisplayI2C::printWaitingForRetireMessage() {
    if (this->lastMessage != WAITING_FOR_RETIRE) {
        this->lastMessage = WAITING_FOR_RETIRE;
        CoffeeDisplayI2C::printWaitingForRetireMessage();
    }
}