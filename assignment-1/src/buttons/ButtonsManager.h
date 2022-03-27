#ifndef BUTTONS_MANAGER_H
#define BUTTONS_MANAGER_H

#include <stdint.h>

class ButtonsManager {

    private:
    static ButtonsManager* currentManager;
    static void handleInterrupt();
    static void attachCurrentManager(ButtonsManager* manager);
    static bool isBouncingInterrupt();

    private:
    uint8_t buttonPins[4];
    volatile bool buttonStates[4];

    public:
    ButtonsManager(uint8_t buttonPins[4]);
    void setup();
    void start();
    void stop();
    bool hasAnyButtonBeenPressed();
    uint8_t getPressedButtonIndex();
    void releasePressedButton();

    private:
    void setButtonPressed(uint8_t index);

};

#endif