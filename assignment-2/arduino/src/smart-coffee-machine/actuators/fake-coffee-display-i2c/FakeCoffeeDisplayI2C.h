#ifndef _FAKE_COFFEE_DISPLAY_I2C_H_
#define _FAKE_COFFEE_DISPLAY_I2C_H_

#include "../coffee-display-i2c/CoffeeDisplayI2C.h"

enum Messages {
    BOOT_MESSAGE,
    READY_MESSAGE,
    SELECTING_INFO_MESSAGE,
    SELECTING_ASSISTANCE_MESSAGE,
    MAKING_INFO_MESSAGE,
    WAITING_FOR_RETIRE_MESSAGE
};

class FakeCoffeeDisplayI2C : public CoffeeDisplayI2C {

    private:
    static FakeCoffeeDisplayI2C* instance;

    public:
    static FakeCoffeeDisplayI2C* getInstance();

    private:
    Messages lastMessage;
    public:
    FakeCoffeeDisplayI2C() {};

    void printBootMessage();
    void printReadyMessage();
    void printSelectingInfoMessage(AppData* appData);
    void printAssistanceMessage();
    void updateMakingInfo(AppData* appData, int percentage);
    void printWaitingForRetireMessage();


};

#endif