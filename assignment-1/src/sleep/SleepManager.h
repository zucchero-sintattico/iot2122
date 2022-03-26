#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <Arduino.h>
#include <EnableInterrupt.h>
#include <avr/sleep.h>

class SleepManager {

    public:
        static uint8_t wakeUpPins[4];
        static void setup(uint8_t wakeUpPins[4]);
        static void sleep();
        static void interruptHandler();
};

#endif