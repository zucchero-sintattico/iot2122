#ifndef GAME_H
#define GAME_H

#include "game-data.h"
#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
#include "potentiometer/PotentiometerManager.h"
#include "ball/BallManager.h"

class Game {

    private:

    float defaultBallMovingSpeed = 1.0;
    unsigned int defaultStoppedBallTime = 5000;
    int minBallMovingTime = 3000;

    GameState currentGameState = WELCOME;
    GameData* gameData;
    FadeManager* fadeManager;
    SleepManager* sleepManager;
    PotentiometerManager* potentiometerManager;
    BallManager* ballManager;


    unsigned long waitingTime = 10000;
    unsigned long prevOperationTimestamp;

    public:
    Game(FadeManager* fadeManager, SleepManager* sleepManager, PotentiometerManager* potentiometerManager, BallManager* ballManager);
    void setup();
    void computeIteration();

    private:
    void changeState(GameState newState);

    void onWelcomeState();
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
    bool isBallMovingTimeElapsed();
    bool isStoppedBallWaitingTimeElapsed();
    bool hasAnyButtonBeenPressed();
    bool hasTimeBetweenBallMovingElapsed();

};

#endif