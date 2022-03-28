#ifndef POTENTIOMETER_MANAGER_H
#define POTENTIOMETER_MANAGER_H

#include <stdint.h>

/**
 * The Potentiometer Manager.
 */
class PotentiometerManager {

private:

    /// The pin of the potentiometer.
    uint8_t potentiometerPin;

    /// The amount of difficulty levels.
    uint8_t difficultyLevels;

public:

    /**
     * Create a new PotentiometerManager.
     * @param potentiometerPin the pin of the potentiometer
     * @param difficultyLevels the amount of difficulty levels
     */
    PotentiometerManager(uint8_t potentiometerPin, uint8_t difficultyLevels = 8);

    /**
     * Setup for pins.
     * ! This method must be called in arduino setup() !
     */
    void setup();

    /**
     * Read the potentiometer.
     * @return the potentiometer value
     */
    int readPotentiometer();

    /**
     * Get the current difficulty level.
     * @return the current difficulty level
     */
    uint8_t getDifficultyLevel();

};

#endif