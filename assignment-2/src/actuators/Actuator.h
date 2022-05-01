#ifndef _ACTUATOR_H_
#define _ACTUATOR_H_

#include "sensor/Setuppable.h"

class Actuator : public Setuppable {
    public:
    // Inherited from Setuppable
    virtual void setup() = 0;
};

#endif