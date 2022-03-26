#ifndef FADE_MANAGER
#define FADE_MANAGER
#include <stdint.h>

/**
 * The Led Fader Manager
 */
class FadeManager {

    private:
        uint8_t fadePin;
        uint8_t fadeIntervalMilliSeconds;

        uint8_t brightness = 5;
        uint8_t fadeAmount;
        unsigned long prevOperationTimestamp;
        
    public:
        /**
        *   @param fadePin the pin to fade
        *   @param fadeIntervalMilliSeconds the interval between brightness increment
        *   @param fadeAmount the value of brightness each steps
        */
        FadeManager(uint8_t fadePin, uint8_t fadeIntervalMilliSeconds, uint8_t fadeAmount);
        
        /**
        *   Setup for pins. Call it in SuperLoop setup
        */
        void setup();
        
        /**
        *   Fade the led
        */
        void fade();

        /**
        *   Switch off the led, ready to start fading again
        */
        void stopFade();

};


#endif