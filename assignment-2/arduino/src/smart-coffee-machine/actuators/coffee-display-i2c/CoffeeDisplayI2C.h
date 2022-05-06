#ifndef _COFFEE_DISPLAY_I2C_H_
#define _COFFEE_DISPLAY_I2C_H_

#include "iot/actuator/display-i2c/DisplayI2C.h"

class CoffeeDisplayI2C : public DisplayI2C {

public:
    CoffeeDisplayI2C() : DisplayI2C() {};
    CoffeeDisplayI2C(int width, int height) : DisplayI2C(width, height) {};
    CoffeeDisplayI2C(int address, int width, int height) : DisplayI2C(address, width, height) {};


    void printReadyMessage();
    void printSelectingInfoMessage();
    void printSelectingAssistanceMessage();
};

#endif