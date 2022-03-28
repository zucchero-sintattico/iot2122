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

    // default values
    unsigned long waitingTime = 10000;
    float defaultBallMovingSpeed = 1.0;
    unsigned int defaultStoppedBallTime = 5000;
    long minBallMovingTime = 3000;

    // Status and data variables
    GameState currentGameState = WELCOME;
    GameData* gameData;

    // Managers
    FadeManager* fadeManager;
    SleepManager* sleepManager;
    PotentiometerManager* potentiometerManager;
    BallManager* ballManager;
    ButtonsManager* buttonsManager;

    // Timestamps for synchronization
    unsigned long sleepWaitingStartTimestamp = 0;
    unsigned long movingBallStartTimestamp = 0;
    unsigned long stoppedBallStartTimestamp = 0;
    unsigned long prevBallMovementTimestamp = 0;

public:

    /**
     * Create a new Game.
     * @param fadingLedPin: The pin of the led to fade.
     * @param potentiometerPin: The pin of the potentiometer.
     * @param ballLedPins: The pins of the balls' leds.
     * @param buttonsPins: The pins of the buttons.
     */
    Game(uint8_t fadingLedPin, uint8_t potentiometerPin, uint8_t ballLedPins[4], uint8_t buttonPins[4]);

    /**
     * Create a new Game.
     * @param fadeManager: The fade manager.
     * @param sleepManager: The sleep manager.
     * @param potentiometerManager: The potentiometer manager.
     * @param ballManager: The ball manager.
     * @param buttonsManager: The buttons manager.
     */
    Game(FadeManager* fadeManager, SleepManager* sleepManager, PotentiometerManager* potentiometerManager, BallManager* ballManager, ButtonsManager* buttonsManager);

    /**
     * Setup the game
     * ! This method must be called in arduino setup() !
     */
    void setup();

    /**
     * Compute a single iteration of the superloop.
     */
    void computeIteration();

private:

    /**
     * Change the actual game state.
     */
    void changeState(GameState newState);


    ///////////////////////////////////////////////////////////////////////////////
    // States
    ///////////////////////////////////////////////////////////////////////////////

    /**
     * Welcome state
     * - Print welcome message
     */
    void onWelcomeState();

    /**
     * Waiting state
     * - Fade the LED
     * - Wait for the user to start the game pressing T1
     */
    void onWaitingState();

    /**
     * Sleep state
     * - Deep sleep
     * - Wait for interrupt to wake up
     */
    void onSleepState();

    /**
     * Game starting state
     * - Setup game variables
     */
    void onGameStartingState();

    /**
     * Round starting state
     * - Setup round variables
     */
    void onRoundStartingState();

    /**
     * Moving ball state
     * - Move the ball
     * - Check when the ball has to be stopped
     */
    void onMovingBallState();

    /**
     * Stopped ball state
     * - Wait for the user to press a button
     * - Check if the user pressed the correct button
     */
    void onStoppedBallState();

    /**
     * End of round state
     * - Increase the score
     */
    void onEndOfRoundState();

    /**
     * End of game state
     * - Print the final score
     * - Reset the game
     */
    void onEndOfGameState();


    ///////////////////////////////////////////////////////////////////////////////
    // Helpers
    ///////////////////////////////////////////////////////////////////////////////

    /**
     * Check if it's time to go in sleep mode.
     * @return true if it's time to go in sleep mode, false otherwise.
     */
    bool isWaitingTimeElapsed();

    /**
     * Check if the user has pressed the starting button.
     * @return true if the user has pressed the starting button, false otherwise.
     */
    bool hasStartingButtonBeenPressed();

    /**
     * Check if it's time to stop the ball.
     * @return true if it's time to stop the ball, false otherwise.
     */
    bool isBallMovingTimeElapsed();

    /**
     * Check if the time to press the button during the stopped ball state has elapsed.
     * @return true if the time to press the button during the stopped ball state has elapsed, false otherwise.
     */
    bool isStoppedBallWaitingTimeElapsed();

    /**
     * Check if it's time to move the ball to next position when in moving ball state.
     * @return true if it's time to move the ball to next position when in moving ball state, false otherwise.
     */
    bool hasTimeBetweenBallMovingElapsed();

    /**
     * Check if the user has pressed the correct button during the stopped ball state.
     * @return true if the user has pressed the correct button during the stopped ball state, false otherwise.
     */
    bool hasUserPressedTheCorrectButton();

};

#endif