#include "DisplayI2C.h"
#include <Arduino.h>

DisplayI2C::DisplayI2C(int address, int width, int height) {
    this->address = address;
    this->lcd = LiquidCrystal_I2C(this->address, width, height);
}

void DisplayI2C::setup() {
    lcd.init();
    lcd.backlight();
}

void DisplayI2C::changeCursor(int column, int row) {
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