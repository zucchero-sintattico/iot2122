#ifndef GAME_DATA
#define GAME_DATA

#include "game-state.h"

/**
 * Game data holder.
 * @param S: The amount of time;
 * @param T1: The time of the first button press;
 * @param T2: The time of the second button press;
 * @param Score: The score;
 * @param currentGameState: The current game state.
 */
struct GameData {
    int S;
    int T1;
    int T2;
    int Score;
    GameState currentGameState;
};

#endif