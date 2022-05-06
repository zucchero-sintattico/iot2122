#ifndef _SUGAR_H_
#define _SUGAR_H_

#include "iot/sensor/potentiometer/Potentiometer.h"

class Sugar : public Potentiometer {

public:
    Sugar(int pin);
    int getPercentage();

};
#endif