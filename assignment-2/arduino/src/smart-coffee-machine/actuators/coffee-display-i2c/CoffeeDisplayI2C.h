#ifndef _COFFEE_DISPLAY_I2C_H_
#define _COFFEE_DISPLAY_I2C_H_
#include "iot/actuator/display-i2c/DisplayI2C.h"
#include "../../config/data/AppData.h"

class CoffeeDisplayI2C : public DisplayI2C {

    public:
    CoffeeDisplayI2C() : DisplayI2C() {};
    CoffeeDisplayI2C(int width, int height) : DisplayI2C(width, height) {};
    CoffeeDisplayI2C(int address, int width, int height) : DisplayI2C(address, width, height) {};

    virtual void setBootingScreen();

    virtual void printWelcomeMessage();
    virtual void printReadyMessage();

    virtual void setSelectingInfoScreen();
    virtual void updateSelectingInfoScreen(AppData* appData);

    virtual void printAssistanceMessage();

    virtual void setMakingInfoScreen(AppData* appData);
    virtual void updateMakingInfo(int percentage);

    virtual void printWaitingForRetireMessage();
};

#endif