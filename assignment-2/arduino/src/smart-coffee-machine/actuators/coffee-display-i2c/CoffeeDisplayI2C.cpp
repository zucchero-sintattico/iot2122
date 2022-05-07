#include "CoffeeDisplayI2C.h"

#define WELCOME_TO "Welcome to"
#define SMART_COFFE "Smart Coffee Machine"
#define READY_MESSAGE "Okay, I'm ready"
#define PRESS_BUTTON_TO_START "(Press any button)"
#define YOU_HAVE_SELECTED "You have selected"
#define SUGAR "Sugar : "
#define PERCENTAGE_SYMBOL " %"
#define ASSISTANCE_MESSAGE "Assistance Required!"
#define PREPARING "Preparing a : "
#define SEPARATOR " : "
#define WATING_FOR "Waiting for"
#define THE_COFFEE "the coffee"
#define TO_BE_RETIRED "to be retired..."

void CoffeeDisplayI2C::printBootMessage() {
    this->clear();
    this->changeCursor(5, 0);
    this->print(WELCOME_TO);
    this->changeCursor(0, 2);
    this->print(SMART_COFFE);
}

void CoffeeDisplayI2C::printReadyMessage() {
    this->clear();
    this->changeCursor(2, 1);
    this->print(READY_MESSAGE);
    this->changeCursor(1, 2);
    this->print(PRESS_BUTTON_TO_START);
}

void CoffeeDisplayI2C::printSelectingInfoMessage(AppData* appData) {
    this->clear();
    this->changeCursor(1, 0);
    this->print(YOU_HAVE_SELECTED);
    this->changeCursor(6, 1);
    this->print(appData->getSelectedBeverageToString());
    this->changeCursor(3, 2);
    this->print(SUGAR + String(appData->getSugarLevel()) + PERCENTAGE_SYMBOL);
}

void CoffeeDisplayI2C::printSelectingAssistanceMessage() {
    this->clear();
    this->changeCursor(0, 1);
    this->print(ASSISTANCE_MESSAGE);
}

void CoffeeDisplayI2C::printMakingInfo(AppData* appData, int percentage) {
    this->clear();
    this->changeCursor(4, 0);
    this->print(PREPARING);
    this->changeCursor(7, 1);
    this->print(appData->getSelectedBeverageToString());
    this->changeCursor(8, 2);
    this->print(String(percentage) + PERCENTAGE_SYMBOL);
}

void CoffeeDisplayI2C::printWaitingForRetireMessage() {
    this->setup();
    this->clear();
    this->changeCursor(4, 0);
    this->print(WATING_FOR);
    this->changeCursor(4, 1);
    this->print(THE_COFFEE);
    this->changeCursor(2, 2);
    this->print(TO_BE_RETIRED);
}