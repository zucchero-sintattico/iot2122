#ifndef _SCHEDULING_STRATEGY_H_
#define _SCHEDULING_STRATEGY_H_

#include <Arduino.h>
class SchedulingStrategy {

protected:
    int elapsedTime = 0;

public:

    void addElapsedTime(int time) {
        this->elapsedTime += time;
    };

    void resetElapsedTime() {
        this->elapsedTime = 0;
    };

    virtual bool hasToBeExecuted() = 0;

};

#endif