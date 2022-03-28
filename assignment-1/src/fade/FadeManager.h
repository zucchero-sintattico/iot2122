#ifndef FADE_MANAGER
#define FADE_MANAGER
#include <stdint.h>

/**
 * The Led Fader Manager
 */
class FadeManager {

private:

    /// The led's pin.
    uint8_t fadePin;

    /// The interval between each fade.
    uint8_t fadeIntervalMilliSeconds;

    /// The current brightness.
    uint8_t brightness = 5;

    /// The fade amount to increment each time.
    uint8_t fadeAmount;

    /// The timestamp of the previous operation.
    unsigned long prevOperationTimestamp;

public:
    /**
    * @param fadePin the pin to fade
    * @param fadeIntervalMilliSeconds the interval between brightness increment
    * @param fadeAmount the value of brightness each steps
    */
    FadeManager(uint8_t fadePin, uint8_t fadeIntervalMilliSeconds = 10, uint8_t fadeAmount = 5);

    /**
    * Setup for pins.
    * ! This method must be called in arduino setup() !
    */
    void setup();

    /**
     * Start the fade.
     */
    void start();

    /**
    * Fade the led.
    */
    void fade();

    /**
    * Switch off the led, ready to start fading again
    */
    void stopFade();

private:

    /**
     * Check if the time elapsed since the last fade operation.
     * @return true if the time elapsed since the last fade operation, false otherwise.
     */
    bool hasTimeElapsedSinceLastFadeOperation();

};


#endif