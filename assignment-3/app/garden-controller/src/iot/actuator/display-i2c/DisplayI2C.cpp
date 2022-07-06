#include "DisplayI2C.h"

DisplayI2C::DisplayI2C(uint8_t address, uint8_t width, uint8_t height) {
    this->address = address;
    this->lcd = LiquidCrystal_I2C(this->address, width, height);
}

void DisplayI2C::setup() {
    lcd.init();
    lcd.backlight();
}

void DisplayI2C::turnOffDisplay() {
    lcd.noBacklight();
}

void DisplayI2C::turnOnDisplay() {
    lcd.backlight();
}

void DisplayI2C::changeCursor(uint8_t row, uint8_t column) {
    this->column = column;
    this->row = row;
}

void DisplayI2C::print(String message) {
    lcd.setCursor(this->column, this->row);
    lcd.print(message);
}

void DisplayI2C::clear() {
    lcd.clear();
}

void DisplayI2C::clearLineFromPosition(uint8_t row, uint8_t column) {
    lcd.setCursor(column, row);
    String filler = "";
    for (uint8_t i = column; i < DEFAULT_WIDTH; i++) {
        filler += " ";
    }
    lcd.print(filler);
}