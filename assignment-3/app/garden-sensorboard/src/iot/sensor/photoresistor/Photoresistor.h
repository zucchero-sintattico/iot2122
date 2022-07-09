#ifndef _PHOTORESISTOR_H_
#define _PHOTORESISTOR_H_

#include <Arduino.h>
#include "../Sensor.h"

class Photoresistor : public Sensor {

    private:
    uint8_t pin;
    uint8_t light;

    public:
    Photoresistor(uint8_t pin);
    void setup();
    void computeRead();
    uint8_t getLight();
};



#endif // _PHOTORESISTOR_H_