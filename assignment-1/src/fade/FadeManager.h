#ifndef FADE_MANAGER
#define FADE_MANAGER
#include <stdint.h>

//#define LIBCALL_ENABLEINTERRUPT

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
    FadeManager(uint8_t fadePin, uint8_t fadeIntervalMilliSeconds = 10, uint8_t fadeAmount = 5);

    /**
    *   Setup for pins. Call it in SuperLoop setup
    */
    void setup();

    void start();

    /**
    *   Fade the led
    */
    void fade();

    /**
    *   Switch off the led, ready to start fading again
    */
    void stopFade();

    private:
    bool hasTimeElapsedSinceLastFadeOperation();

};


#endif