#ifndef GAME_H
#define GAME_H

#include "game-data.h"
#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
#include "potentiometer/PotentiometerManager.h"

class Game {

    private:
        GameData *gameData;
        FadeManager *fadeManager;
        SleepManager *sleepManager;
        PotentiometerManager *potentiometerManager;


        unsigned long waitingTime = 10000;
        unsigned long prevOperationTimestamp;

    public:
        Game(GameData *gameData, FadeManager *fadeManager, SleepManager *sleepManager, PotentiometerManager *potentiometerManager);
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

        bool isWaitingTimeElapsed();
        bool hasStartingButtonBeenPressed();

};

#endif