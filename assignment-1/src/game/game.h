#include "game-data.h"
#include "fade/FadeManager.h"
#ifndef GAME_H
#define GAME_H

class Game {

    private:
        GameData *gameData;
        FadeManager *fadeManager;

        unsigned long prevOperationTimestamp;

    public:
        Game(GameData *gameData, FadeManager *fadeManager);
        void setup();
        void computeIteration();

    private:
        void changeState(GameState newState);

        void onWaitingState();
        void onSleepState();
        void onGameStartingState();
        void onRoundStartingState();
        void onMovingBallState();
        void onStoppedBallState();
        void onEndOfRoundState();
        void onEndOfGameState();

};

#endif