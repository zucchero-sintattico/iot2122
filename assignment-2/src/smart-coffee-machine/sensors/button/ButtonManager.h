#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

#include "iot/sensor/SensorManager.h"

class ButtonManager : public SensorManager {

    private:
    int pin;
    bool isButtonPressed = false;
    bool prevValue = false;

    public:
    ButtonManager(int pin);
    bool isPressed();

    void setup();
    void computeRead();

};

#endif