#ifndef BALL_MANAGER_H
#define BALL_MANAGER_H

#include <stdint.h>

class BallManager {

    private:
    uint8_t ledPins[4];
    int prevLedIndexPosition;
    int actualLedIndexPosition;
    int directionalIncrement = 1;

    public:
    BallManager(uint8_t ledPins[4]);
    void setup();
    void start();
    void nextBall();

    private:
    bool isDirectionChangeNeeded();
    void changeDirection();
    void incrementPosition();
    void turnOffPreviousLedIfPresent();
    void turnOnActualLed();
};

#endif