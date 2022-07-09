#ifndef _THERMOMETER_H_
#define _THERMOMETER_H_

#include <Arduino.h>
#include "../Sensor.h"
#define AREF_VOLTAGE 3.3

class Thermometer : public Sensor {

    private:
    uint8_t pin;
    uint8_t temperature;

    public:
    Thermometer(uint8_t pin);
    void setup();
    void computeRead();
    uint8_t getTemperature();
    String toString();
};



#endif // _THERMOMETER_H_