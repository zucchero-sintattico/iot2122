#ifndef _PIR_H_
#define _PIR_H_

#include "../Sensor.h"
#include <Arduino.h>

class Pir : public Sensor {

    private:
    uint8_t pin;
    bool detection;
    int calibrationTimeMS = 10000;

    public:
    Pir(uint8_t pin);
    uint8_t getPin();
    bool isSomeoneDetected();

    void setup();
    void computeRead();

};

#endif