#include <Arduino.h>

#include "config.h"
#include "potentiometer/potentiometer.h"
#include "fade/fade.h"
//#include "sleep/sleep.h"

#include "game/game-state.h"

GameState currentGameState = WAITING;

int T1 = 0;
int T2 = 0;
int S = 0;

void setup() {
  Serial.begin(9600);
  fadeSetup();
  //pinMode(2, INPUT);
  //attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
}

void loop() {
  switch (currentGameState) {
    case WAITING: onWaitingState(); break;
    case SLEEP: onSleepState(); break;
    case GAME_STARTING: onRoundStartingState(); break;
    case ROUND_STARTING: onRoundStartingState(); break;
    case MOVING_BALL: onMovingBallState(); break;
    case STOPPED_BALL: onStoppedBallState(); break;
    case END_OF_ROUND: onEndOfRoundState(); break;
    case END_OF_GAME: onEndOfGameState(); break;
  }
}

void onWaitingState() {
  //TODO: fade
  //TODO: Check if 10 seconds has passed
    currentGameState = SLEEP;

  //TODO: Check if button 1 is pressed
    currentGameState = GAME_STARTING;
}

void onSleepState() {
  //TODO: goToSleep();
  currentGameState = WAITING;
}

void onGameStartingState() {
  // TODO: Setup game variables (S, T2, Score)
  currentGameState = ROUND_STARTING;
}


void onRoundStartingState() {
  // TODO: Select a Random T1
  currentGameState = MOVING_BALL;
}

void onMovingBallState() {
  // TODO: until T1 seconds has passed
    // TODO: every S velocity
      // TODO: move ball to the next one

  currentGameState = STOPPED_BALL;
}


void onStoppedBallState() {
  // TODO: until T2 seconds has passed
    // TODO: Check if a button is pressed
      
      // TODO: if the button was correct:
        currentGameState = END_OF_ROUND;
      // TODO: else:
        currentGameState = END_OF_GAME;

  // TODO: else:
    currentGameState = END_OF_GAME;
}

void onEndOfRoundState() {
  // TODO: Increase S and decrease T2 
  // TODO: Increase Score
  currentGameState = ROUND_STARTING;
}

void onEndOfGameState() {
  // TODO: print results
  currentGameState = WAITING;
}

void wakeUp(){
  Serial.println("Ciao mi sono svegliato");
}
