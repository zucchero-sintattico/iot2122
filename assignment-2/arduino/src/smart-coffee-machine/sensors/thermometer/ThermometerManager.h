#ifndef _THERMOMETER_H_
#define _THERMOMETER_H_

#include <Arduino.h>
#include "iot/sensor/SensorManager.h"
#define AREF_VOLTAGE 3.3

class ThermometerManager : public SensorManager {

    private:
    int pin;
    uint8_t temperature;

    public:
    ThermometerManager(int pin);
    void setup();
    void computeRead();
    uint8_t getTemperature();
    String toString();
};



#endif // _THERMOMETER_H_