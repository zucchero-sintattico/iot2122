#ifndef _PIR_H_
#define _PIR_H_

#include "../Sensor.h"

class Pir : public Sensor {

private:
    int pin;
    bool detection;
    int calibrationTimeMS = 10000;

public:
    Pir(int pin);
    bool isSomeoneDetected();

    void setup();
    void computeRead();

};

#endif