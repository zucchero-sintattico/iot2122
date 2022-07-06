
#ifndef _DIGITAL_LED_H_
#define _DIGITAL_LED_H_
#include "iot/actuator/actuator.h"
#include <Arduino.h>

class DigitalLed : public Actuator {

    private:
    uint8_t pin;
    bool isActive;

    public:
    DigitalLed(uint8_t pin);
    void setup();
    void setActive(bool isActive);
};

#endif
