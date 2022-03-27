#ifndef GAME_H
#define GAME_H

#include "game-data.h"
#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
#include "potentiometer/PotentiometerManager.h"
#include "ball/BallManager.h"
#include "buttons/ButtonsManager.h"

class Game {

    private:

    float defaultBallMovingSpeed = 1.0;
    unsigned int defaultStoppedBallTime = 5000;
    long minBallMovingTime = 3000;

    GameState currentGameState = WELCOME;
    GameData* gameData;
    FadeManager* fadeManager;
    SleepManager* sleepManager;
    PotentiometerManager* potentiometerManager;
    BallManager* ballManager;
    ButtonsManager* buttonsManager;


    unsigned long waitingTime = 10000;
    unsigned long sleepWaitingStartTimestamp = 0;
    unsigned long movingBallStartTimestamp = 0;
    unsigned long stoppedBallStartTimestamp = 0;
    unsigned long prevBallMovementTimestamp = 0;

    public:
    Game(uint8_t fadingLedPin, uint8_t potentiometerPin, uint8_t ballLedPins[4], uint8_t buttonPins[4]);
    Game(FadeManager* fadeManager, SleepManager* sleepManager, PotentiometerManager* potentiometerManager, BallManager* ballManager, ButtonsManager* buttonsManager);
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
    bool hasTimeBetweenBallMovingElapsed();
    bool hasUserPressedTheCorrectButton();

};

#endif