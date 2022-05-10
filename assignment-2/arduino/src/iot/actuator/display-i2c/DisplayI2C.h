#ifndef _DISPLAY_I2C_H_
#define _DISPLAY_I2C_H_

#include "iot/actuator/Actuator.h"
#include <LiquidCrystal_I2C.h>
#include <Arduino.h>


#define DEFAULT_ADDRESS 0x27
#define DEFAULT_WIDTH  20
#define DEFAULT_HEIGHT  4

class DisplayI2C : public Actuator {
    private:
    uint8_t address = 0x27;
    uint8_t column = 0;
    uint8_t row = 0;
    LiquidCrystal_I2C lcd = LiquidCrystal_I2C(address, DEFAULT_WIDTH, DEFAULT_HEIGHT);

    public:
    DisplayI2C() : DisplayI2C(DEFAULT_ADDRESS, DEFAULT_WIDTH, DEFAULT_HEIGHT) {};
    DisplayI2C(uint8_t width, uint8_t height) : DisplayI2C(DEFAULT_ADDRESS, width, height) {};
    DisplayI2C(uint8_t address, uint8_t width, uint8_t height);
    void setup();
    void turnOffDisplay();
    void turnOnDisplay();
    void changeCursor(uint8_t row, uint8_t column);
    void print(String message);
    void clear();
    void clearLineFromPosition(uint8_t row, uint8_t column);
};

#endif //DISPLAYMANAGER_H