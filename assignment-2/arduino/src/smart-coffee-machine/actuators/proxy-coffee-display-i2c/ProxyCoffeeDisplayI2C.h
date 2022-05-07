#ifndef _PROXY_COFFEE_DISPLAY_I2C_H_
#define _PROXY_COFFEE_DISPLAY_I2C_H_

#include "../coffee-display-i2c/CoffeeDisplayI2C.h"


enum ProxyMessage {
    BOOT,
    READY,
    SELECTING_INFO,
    SELECTING_ASSISTANCE,
    MAKING_INFO,
    WAITING_FOR_RETIRE
};

class ProxyCoffeeDisplayI2C : public CoffeeDisplayI2C {

    private:
    ProxyMessage lastMessage;
    public:
    ProxyCoffeeDisplayI2C() : CoffeeDisplayI2C() {};
    ProxyCoffeeDisplayI2C(int width, int height) : CoffeeDisplayI2C(width, height) {};
    ProxyCoffeeDisplayI2C(int address, int width, int height) : CoffeeDisplayI2C(address, width, height) {};

    virtual void printBootMessage();
    virtual void printReadyMessage();
    virtual void printSelectingInfoMessage(AppData* appData);
    virtual void printSelectingAssistanceMessage();
    virtual void printMakingInfo(AppData* appData, int percentage);
    virtual void printWaitingForRetireMessage();
};
#endif