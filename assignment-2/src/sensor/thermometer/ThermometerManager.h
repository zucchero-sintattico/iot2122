#ifndef _THERMOMETER_H_
#define _THERMOMETER_H_
#define AREF_VOLTAGE 3.3
#include <Arduino.h>
#include "../SensorManager.h"
#include "../Setuppable.h"

class ThermometerManager : public SensorManager{

    private:
        int pin;
        uint8_t temperature;
    
    public:
        ThermometerManager(int pin);
        void setup();
        void computeRead();
        uint8_t getThemperature();
        String toString();
};



#endif // _THERMOMETER_H_