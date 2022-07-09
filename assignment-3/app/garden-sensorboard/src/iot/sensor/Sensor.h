#ifndef _SENSOR_H_
#define _SENSOR_H_

#include "./Setuppable.h"

class Sensor : public Setuppable {

public:
    virtual void computeRead() = 0;
};

#endif