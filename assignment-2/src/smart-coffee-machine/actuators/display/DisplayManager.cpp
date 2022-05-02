#include "DisplayManager.h"
#include <Arduino.h>

DisplayManager::DisplayManager(int address, int width, int height){
    this->address = address;
    this->lcd = LiquidCrystal_I2C(this->address, width, height);
}

void DisplayManager::setup(){
    lcd.init();
    lcd.backlight();
}

void DisplayManager::changeCursor(int column, int row){
    this->column = column;
    this->row = row;
}

void DisplayManager::print(String message){
    lcd.setCursor(this->column, this->row);
    lcd.print(message);
}

void DisplayManager::clear(){
    lcd.clear();
}