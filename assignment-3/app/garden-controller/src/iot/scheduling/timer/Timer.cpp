#include "Timer.h"
#include "Arduino.h"
#include <MsTimer2.h>

volatile bool timerFlag;

void interrupt() {
    timerFlag = true;
}

Timer::Timer() {
    timerFlag = false;
}

void Timer::setupFreq(int freq) {
    this->setupPeriod(1000 / freq);
}

/* period in ms */
void Timer::setupPeriod(int period) {
    MsTimer2::set(period, interrupt);
    MsTimer2::start();
}

void Timer::waitForNextTick() {
    /* wait for timer signal */
    while (!timerFlag) {}
    timerFlag = false;
}