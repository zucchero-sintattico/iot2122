
#ifndef _ANALOG_LED_H_
#define _ANALOG_LED_H_
#include "iot/actuator/actuator.h"
#include <Arduino.h>

class AnalogLed : public Actuator {

    private:
    uint8_t pin;
    uint8_t value;

    public:
    AnalogLed(uint8_t pin);
    void setup();
    void setValue(uint8_t value);
};

#endif
