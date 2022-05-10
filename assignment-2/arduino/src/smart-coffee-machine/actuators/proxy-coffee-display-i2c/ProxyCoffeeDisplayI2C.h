#ifndef _PROXY_COFFEE_DISPLAY_I2C_H_
#define _PROXY_COFFEE_DISPLAY_I2C_H_

#include "../coffee-display-i2c/CoffeeDisplayI2C.h"


enum ProxyMessage {
    SET_BOOTING_SCREEN,
    WELCOME_MESSAGE,
    READY,
    SET_SELECTING_INFO,
    UPDATE_SET_SELECTING_INFO,
    SET_MAKING_INFO,
    UPDATE_MAKING_INFO,
    ASSISTANCE_MESSAGE,
    WAITING_FOR_RETIRE,
    SET_MECHANIC_CHECK_INFO,
    UPDATE_MECHANIC_CHECK_INFO
};

class ProxyCoffeeDisplayI2C : public CoffeeDisplayI2C {

    private:
    static ProxyCoffeeDisplayI2C* _instance;
    public:
    static ProxyCoffeeDisplayI2C* getInstance();

    private:
    ProxyMessage lastMessage;
    Beverage lastBeverage = COFFEE;
    uint8_t lastSugarLevel = 0;
    uint8_t lastPercentage = 0;
    public:
    ProxyCoffeeDisplayI2C() : CoffeeDisplayI2C() {};
    ProxyCoffeeDisplayI2C(int width, int height) : CoffeeDisplayI2C(width, height) {};
    ProxyCoffeeDisplayI2C(int address, int width, int height) : CoffeeDisplayI2C(address, width, height) {};

    virtual void setBootingScreen();

    virtual void printWelcomeMessage();
    virtual void printReadyMessage();

    virtual void setSelectingInfoScreen();
    virtual void updateSelectingInfoScreen(AppData* appData);

    virtual void printAssistanceMessage();

    virtual void setMakingInfoScreen(AppData* appData);
    virtual void updateMakingInfo(int percentage);

    virtual void printWaitingForRetireMessage();

    virtual void setMechanicCheckInfoScreen();
    virtual void updateMechanicCheckInfo(int percentage);

};
#endif