#ifndef _BUTTON_H
#define _BUTTON_H

#include "../Sensor.h"

class Button : public Sensor {

private:
    int pin;
    bool isButtonPressed = false;
    bool prevValue = false;

public:
    Button(int pin);
    bool isPressed();

    void setup();
    void computeRead();

};

#endif