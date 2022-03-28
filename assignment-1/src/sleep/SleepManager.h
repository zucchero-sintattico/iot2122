#ifndef SLEEP_MANAGER_H
#define SLEEP_MANAGER_H

#include <stdint.h>

/**
 * The Sleep Manager.
 */
class SleepManager {

    /// The pins that will be used to wake up the device.
    uint8_t wakeUpPins[4];

public:

    /**
     * Create a new SleepManager.
     * @param wakeUpPins the pins that will be used to wake up the device
     */
    SleepManager(uint8_t wakeUpPins[4]);

    /**
     * Setup for pins.
     * ! This method must be called in arduino setup() !
     */
    void setup();

    /**
     * Put the device to sleep and wait until the device wakes up after a wake up pin is pressed.
     */
    void sleep();
};


#endif