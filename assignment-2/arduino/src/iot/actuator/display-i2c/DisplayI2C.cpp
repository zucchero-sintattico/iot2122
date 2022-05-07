#include "DisplayI2C.h"

DisplayI2C::DisplayI2C(uint8_t address, uint8_t width, uint8_t height) {
    this->address = address;
    this->lcd = LiquidCrystal_I2C(this->address, width, height);
}

void DisplayI2C::setup() {
    lcd.init();
    lcd.backlight();
}

void DisplayI2C::changeCursor(uint8_t column, uint8_t row) {
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