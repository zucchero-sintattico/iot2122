#ifndef _COFFEE_DISPLAY_I2C_H_
#define _COFFEE_DISPLAY_I2C_H_

#include "iot/actuator/display-i2c/DisplayI2C.h"
#include "../../config/data/AppData.h"

class CoffeeDisplayI2C : public DisplayI2C {

public:
    CoffeeDisplayI2C() : DisplayI2C() {};
    CoffeeDisplayI2C(int width, int height) : DisplayI2C(width, height) {};
    CoffeeDisplayI2C(int address, int width, int height) : DisplayI2C(address, width, height) {};

    virtual void printBootMessage() = 0;
    virtual void printReadyMessage() = 0;
    virtual void printSelectingInfoMessage(AppData* appData) = 0;
    virtual void printSelectingAssistanceMessage() = 0;
    virtual void printMakingInfo(AppData* appData, int percentage) = 0;
    virtual void printWaitingForRetireMessage() = 0;
};

#endif