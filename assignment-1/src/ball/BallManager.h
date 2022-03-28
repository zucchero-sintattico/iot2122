#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

#include <stdint.h>

/**
 * The Ball Manager.
 */
class BallManager {

private:
    /// The leds's pins.
    uint8_t ledPins[4];

    /// The previous ball index position.
    int prevLedIndexPosition;

    /// The current ball index position.
    int actualLedIndexPosition;

    /// The directional increment of the ball (1 for left to right, -1 for right to left).
    int directionalIncrement = 1;

public:

    /**
     * Create a new Ball Manager.
     * @param ledPins the led's pins to fade
     */
    BallManager(uint8_t ledPins[4]);

    /**
     * Setup the leds.
     * ! This method must be called in arduino setup() !
     */
    void setup();

    /**
     * Start the ball bouncing.
     */
    void start();

    /**
     * Stop the ball bouncing.
     */
    void stop();

    /**
     * Move the ball to the next led.
     */
    void nextBall();

    /**
     * Get the actual led index position.
     * @return the actual led index position.
     */
    uint8_t getCurrentBallIndex();

private:

    /**
     * Check if we need to change the direction of the ball.
     * @return true if we need to change the direction of the ball, false otherwise.
     */
    bool isDirectionChangeNeeded();

    /**
     * Change the direction of the ball.
     */
    void changeDirection();

    /**
     * Incremenet the led index position.
     */
    void incrementPosition();

    /**
     * Turn off the previous led.
     */
    void turnOffPreviousLedIfPresent();

    /**
     * Turn on the actual led.
     */
    void turnOnActualLed();
};

#endif