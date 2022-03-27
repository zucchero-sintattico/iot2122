#include "game.h"

#include <Arduino.h>

Game::Game(FadeManager* fadeManager, SleepManager* sleepManager, PotentiometerManager* potentiometerManager, BallManager* ballManager) {
  this->fadeManager = fadeManager;
  this->sleepManager = sleepManager;
  this->potentiometerManager = potentiometerManager;
  this->ballManager = ballManager;
}

void Game::setup() {
  this->fadeManager->setup();
  this->sleepManager->setup();
  this->potentiometerManager->setup();
  this->ballManager->setup();
  this->prevOperationTimestamp = millis();
}

void Game::computeIteration() {
  switch (this->currentGameState) {
  case WELCOME: this->onWelcomeState(); break;
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

///////////////////////////////////////////////////////////////////////////////
// Utilities
///////////////////////////////////////////////////////////////////////////////


void Game::changeState(GameState newState) {
  this->currentGameState = newState;
}

bool Game::isWaitingTimeElapsed() {
  return (millis() - this->prevOperationTimestamp) > this->waitingTime;
}

bool Game::hasStartingButtonBeenPressed() {
  // TODO: Implement
}

bool Game::isBallMovingTimeElapsed() {
  return (millis() - this->prevOperationTimestamp) > this->gameData->ballMovingDuration;
}


bool Game::isStoppedBallWaitingTimeElapsed() {
  return (millis() - this->prevOperationTimestamp) > this->gameData->stoppedBallTime;
}

bool Game::hasAnyButtonBeenPressed() {
  // TODO: Implement
}

bool Game::hasTimeBetweenBallMovingElapsed() {
  return millis() - this->prevOperationTimestamp > 1000 / this->gameData->ballMovingDuration;
}


////////////////////////////////////////////////////////////////////////////////
// States
////////////////////////////////////////////////////////////////////////////////

void Game::onWelcomeState() {
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start.");
  this->changeState(WAITING);
}

void Game::onSleepState() {
  this->sleepManager->sleep();
  this->changeState(WELCOME);
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

void Game::onGameStartingState() {
  this->gameData = new GameData({
    ballMovingSpeed: 0,
    ballMovingDuration : 0,
    stoppedBallTime : this->defaultStoppedBallTime,
    difficultyFactor : this->potentiometerManager->getDifficultyFactor(),
    score : 0
    });

  Serial.println("GO!");
  this->changeState(ROUND_STARTING);
}

void Game::onRoundStartingState() {
  this->gameData->ballMovingDuration = this->minBallMovingTime + random(2000 + 1);
  this->prevOperationTimestamp = millis();
  this->changeState(MOVING_BALL);
}

void Game::onMovingBallState() {
  if (this->isBallMovingTimeElapsed()) {
    this->changeState(STOPPED_BALL);
  }
  else {
    if (this->hasTimeBetweenBallMovingElapsed()) {
      this->ballManager->nextBall();
      this->prevOperationTimestamp = millis();
    }
  }
}

void Game::onStoppedBallState() {
  if (this->isStoppedBallWaitingTimeElapsed()) {
    // TODO: onExit
    this->changeState(END_OF_GAME);
  }
  else {
    if (this->hasAnyButtonBeenPressed()) {
      // TODO: this->getPressedButton() == this->ballManager->getCurrentBall()
      if (1) {
        // TODO: onCorrectButtonPressed
        this->changeState(END_OF_ROUND);
      }
      else {
        this->changeState(END_OF_GAME);
      }
    }
  }
}

void Game::onEndOfRoundState() {
  this->gameData->ballMovingSpeed *= (1.1 + this->potentiometerManager->getDifficultyFactor());
  this->gameData->stoppedBallTime /= (1.1 + this->potentiometerManager->getDifficultyFactor());
  this->gameData->score++;
  this->changeState(ROUND_STARTING);
}

void Game::onEndOfGameState() {
  // TODO: print results
  this->changeState(WAITING);
}