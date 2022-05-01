#ifndef _BUTTON_MANAGER_H_
#define _BUTTON_MANAGER_H_

#include "iot/sensor/SensorManager.h"

class ButtonManager : public SensorManager {

    private:
    int pin;
    bool isButtonPressed;

    public:
    ButtonManager(int pin);
    bool isPressed();

    void setup();
    void computeRead();

};

#endif