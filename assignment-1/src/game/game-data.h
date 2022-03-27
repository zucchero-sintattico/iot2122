#ifndef GAME_DATA
#define GAME_DATA

#include <stdint.h>
#include "game-state.h"

/**
 * Game data holder.
 * @param ballMovingSpeed(S): The amount of time;
 * @param ballMovingDuration(T1): The time of the first button press;
 * @param stoppedBallTime(T2): The time of the second button press;
 * @param difficultyFactor(F): The difficulty factor.
 * @param score: The score;
 */
struct GameData {
    float ballMovingSpeed;
    unsigned int ballMovingDuration;
    unsigned int stoppedBallTime;
    uint8_t difficultyFactor;
    int score;
};

#endif