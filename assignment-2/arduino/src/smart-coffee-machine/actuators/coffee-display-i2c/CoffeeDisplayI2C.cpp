#include "CoffeeDisplayI2C.h"

#define BOOTING "Booting..."
#define WELCOME_TO "Welcome to"
#define SMART_COFFEE_MACHINE "Smart Coffee Machine"
#define READY_MESSAGE "Ready"
#define PRESS_BUTTON_TO_START "(Press any button)"
#define BEVERAGE "Beverage: "
#define SUGAR "Sugar: "
#define PERCENTAGE_SYMBOL "%"
#define ASSISTANCE_MESSAGE "Assistance Required!"
#define PREPARING "Preparing a : "
#define WATING_FOR "Waiting for"
#define THE_BEVERAGE "the beverage"
#define TO_BE_RETIRED "to be retired..."
#define MECHANIC_CHECK "Mechanic Check: "

void CoffeeDisplayI2C::setBootingScreen() {
    this->clear();
    this->changeCursor(1, 5);
    print(BOOTING);
}

void CoffeeDisplayI2C::printWelcomeMessage() {
    this->clear();
    this->changeCursor(0, 5);
    this->print(WELCOME_TO);
    this->changeCursor(2, 0);
    this->print(SMART_COFFEE_MACHINE);
}

void CoffeeDisplayI2C::printReadyMessage() {
    this->clear();
    this->changeCursor(1, 8);
    this->print(READY_MESSAGE);
    this->changeCursor(2, 1);
    this->print(PRESS_BUTTON_TO_START);
}

void CoffeeDisplayI2C::setSelectingInfoScreen() {
    this->clear();
    this->changeCursor(0, 0);
    this->print(BEVERAGE);
    this->changeCursor(2, 0);
    this->print(SUGAR);
}

void CoffeeDisplayI2C::updateSelectingInfoScreen(AppData* appData) {
    this->changeCursor(0, 10);
    this->clearLineFromPosition(0, 10);
    this->print(appData->getSelectedBeverageToString());
    this->changeCursor(2, 8);
    this->clearLineFromPosition(2, 8);
    this->print(String(appData->getSugarLevel()) + PERCENTAGE_SYMBOL);
}

void CoffeeDisplayI2C::printAssistanceMessage() {
    this->clear();
    this->changeCursor(1, 0);
    this->print(ASSISTANCE_MESSAGE);
}

void CoffeeDisplayI2C::setMakingInfoScreen(AppData* appData) {
    this->clear();
    this->changeCursor(0, 4);
    this->print(PREPARING);
    this->changeCursor(1, 7);
    this->print(appData->getSelectedBeverageToString());
}

void CoffeeDisplayI2C::updateMakingInfo(int percentage) {
    this->changeCursor(2, 8);
    this->clearLineFromPosition(2, 8);
    this->print(String(percentage) + PERCENTAGE_SYMBOL);
}

void CoffeeDisplayI2C::printWaitingForRetireMessage() {
    this->clear();
    this->changeCursor(0, 4);
    this->print(WATING_FOR);
    this->changeCursor(1, 4);
    this->print(THE_BEVERAGE);
    this->changeCursor(2, 2);
    this->print(TO_BE_RETIRED);
}

void CoffeeDisplayI2C::setMechanicCheckInfoScreen() {
    this->clear();
    this->changeCursor(1, 2);
    this->print(MECHANIC_CHECK);
}

void CoffeeDisplayI2C::updateMechanicCheckInfo(int percentage) {
    this->changeCursor(2, 8);
    this->clearLineFromPosition(2, 8);
    this->print(String(percentage) + PERCENTAGE_SYMBOL);
}