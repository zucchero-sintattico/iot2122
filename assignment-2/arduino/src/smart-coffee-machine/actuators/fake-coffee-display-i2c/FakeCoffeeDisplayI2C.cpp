#include "FakeCoffeeDisplayI2C.h"

#include <Arduino.h>

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

void FakeCoffeeDisplayI2C::printSelectingAssistanceMessage() {
    if (lastMessage != SELECTING_ASSISTANCE_MESSAGE) {
        Serial.println("");
        lastMessage = SELECTING_ASSISTANCE_MESSAGE;
    }
    Serial.print("\rFakeCoffeeDisplayI2C::printSelectingAssistanceMessage");
}