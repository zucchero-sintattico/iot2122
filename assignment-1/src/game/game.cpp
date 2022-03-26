#include "game.h"

#include <Arduino.h>

Game::Game(GameData *gameData, FadeManager *fadeManager, SleepManager *sleepManager, PotentiometerManager *potentiometerManager) {
  this->gameData = gameData;
  this->fadeManager = fadeManager;
  this->sleepManager = sleepManager;
  this->potentiometerManager = potentiometerManager;
}

void Game::setup() {
  this->fadeManager->setup();
  this->sleepManager->setup();
  this->potentiometerManager->setup();

  
  this->prevOperationTimestamp = millis();
}

void Game::computeIteration() {
  switch (this->gameData->currentGameState) {
    case WAITING: this->onWaitingState(); break;
    case SLEEP: this->onSleepState(); break;
    case GAME_STARTING: this->onGameStartingState(); break;
    case ROUND_STARTING: this->onRoundStartingState(); break;
    case MOVING_BALL: this->onMovingBallState(); break;
    case STOPPED_BALL: this->onStoppedBallState(); break;
    case END_OF_ROUND: this->onEndOfRoundState(); break;
    case END_OF_GAME: this->onEndOfGameState(); break;
  }
}

void Game::changeState(GameState newState) {
  this->gameData->currentGameState = newState;
}

bool Game::isWaitingTimeElapsed() {
  return (millis() - this->prevOperationTimestamp) > this->waitingTime;
}

bool Game::hasStartingButtonBeenPressed() {
  // TODO: Implement
}

void Game::onWaitingState() {
  this->fadeManager->fade();

  if (this->isWaitingTimeElapsed()) {
    this->changeState(SLEEP);
  }

  if (this->hasStartingButtonBeenPressed()) {
    this->changeState(GAME_STARTING);
  }
}


void Game::onSleepState() {
  this->sleepManager->sleep();
  this->changeState(WAITING);
}

void Game::onGameStartingState() {
  // TODO: Setup game variables (S, T2, Score)
  this->changeState(ROUND_STARTING);
}


void Game::onRoundStartingState() {
  // TODO: Select a Random T1
  this->changeState(MOVING_BALL);
}

void Game::onMovingBallState() {
  // TODO: until T1 seconds has passed
    // TODO: every S velocity
      // TODO: move ball to the next one
  
  this->changeState(STOPPED_BALL);
}


void Game::onStoppedBallState() {
  // TODO: until T2 seconds has passed
    // TODO: Check if a button is pressed
      
      // TODO: if the button was correct:
        this->changeState(END_OF_ROUND);
      // TODO: else:
        this->changeState(END_OF_GAME);

  // TODO: else:
    this->changeState(END_OF_GAME);
}

void Game::onEndOfRoundState() {
  // TODO: Increase S and decrease T2 
  // TODO: Increase Score
  this->changeState(ROUND_STARTING);
}

void Game::onEndOfGameState() {
  // TODO: print results
  this->changeState(WAITING);
}