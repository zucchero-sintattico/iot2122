#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <stdint.h>

class SleepManager {

    uint8_t wakeUpPins[4];

    public:
        SleepManager(uint8_t wakeUpPins[4]);
        void setup();
        void sleep();
};


#endif