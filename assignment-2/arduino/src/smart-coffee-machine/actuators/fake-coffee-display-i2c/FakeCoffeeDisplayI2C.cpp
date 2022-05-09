#include "FakeCoffeeDisplayI2C.h"

#include <Arduino.h>


FakeCoffeeDisplayI2C* FakeCoffeeDisplayI2C::instance = nullptr;
FakeCoffeeDisplayI2C* FakeCoffeeDisplayI2C::getInstance() {
    if (instance == nullptr) {
        instance = new FakeCoffeeDisplayI2C();
    }
    return instance;
}

void FakeCoffeeDisplayI2C::printWelcomeMessage() {
    if (lastMessage != BOOT_MESSAGE) {
        Serial.println("");
        lastMessage = BOOT_MESSAGE;
    }
    Serial.print("\rWelcome to Smart Coffee Machine!");
}


void FakeCoffeeDisplayI2C::printReadyMessage() {
    if (lastMessage != READY_MESSAGE) {
        Serial.println("");
        lastMessage = READY_MESSAGE;
    }
    Serial.print("\rREADY (Press any button to start)");
}

void FakeCoffeeDisplayI2C::printSelectingInfoMessage(AppData* appData) {
    if (lastMessage != SELECTING_INFO_MESSAGE) {
        Serial.println("");
        lastMessage = SELECTING_INFO_MESSAGE;
    }
    String spaces = appData->getSelectedBeverage() == COFFEE ? "      " :
        appData->getSelectedBeverage() == TEA ? "         " :
        "   ";
    Serial.print("\rBeverage: " + appData->getSelectedBeverageToString() + spaces + "Sugar: " + String(appData->getSugarLevel()) + "%   ");
}

void FakeCoffeeDisplayI2C::printAssistanceMessage() {
    if (lastMessage != SELECTING_ASSISTANCE_MESSAGE) {
        Serial.println("");
        lastMessage = SELECTING_ASSISTANCE_MESSAGE;
    }
    Serial.print("\rFakeCoffeeDisplayI2C::printSelectingAssistanceMessage");
}

void FakeCoffeeDisplayI2C::updateMakingInfo(AppData* appData, int percentage) {
    if (lastMessage != MAKING_INFO_MESSAGE) {
        Serial.println("");
        lastMessage = MAKING_INFO_MESSAGE;
    }
    Serial.print("\rPreparing a " + String(appData->getSelectedBeverageToString()) + " : " + String(percentage) + "%");
}

void FakeCoffeeDisplayI2C::printWaitingForRetireMessage() {
    if (lastMessage != WAITING_FOR_RETIRE_MESSAGE) {
        Serial.println("");
        lastMessage = WAITING_FOR_RETIRE_MESSAGE;
    }
    Serial.print("\rWaiting for the coffee to be retired...");
}