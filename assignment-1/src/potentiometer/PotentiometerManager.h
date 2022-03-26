#ifndef POTENTIOMETER_MANAGER_H
#define POTENTIOMETER_MANAGER_H

#include <stdint.h>

class PotentiometerManager {

    private: 
        uint8_t potentiometerPin;
        uint8_t difficultyLevels;
    
    public:
        PotentiometerManager(uint8_t potentiometerPin, uint8_t difficultyLevels);
        void setup();
        int readPotentiometer();
        uint8_t getDifficulty();

};

#endif