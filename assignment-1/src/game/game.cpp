#include "game.h"

#include <Arduino.h>

Game::Game(uint8_t fadingLedPin, uint8_t potentiometerPin, uint8_t ballLedPins[4], uint8_t buttonPins[4]) {
  this->fadeManager = new FadeManager(fadingLedPin);
  this->sleepManager = new SleepManager(buttonPins);
  this->potentiometerManager = new PotentiometerManager(potentiometerPin);
  this->ballManager = new BallManager(ballLedPins);
  this->buttonsManager = new ButtonsManager(buttonPins);
}

Game::Game(FadeManager* fadeManager, SleepManager* sleepManager, PotentiometerManager* potentiometerManager, BallManager* ballManager, ButtonsManager* buttonsManager) {
  this->fadeManager = fadeManager;
  this->sleepManager = sleepManager;
  this->potentiometerManager = potentiometerManager;
  this->ballManager = ballManager;
  this->buttonsManager = buttonsManager;
}

void Game::setup() {
  // Setup managers
  this->fadeManager->setup();
  this->sleepManager->setup();
  this->potentiometerManager->setup();
  this->ballManager->setup();
  this->buttonsManager->setup();


  this->buttonsManager->start(); // enable buttons-interrupt
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
  return (millis() - this->sleepWaitingStartTimestamp) > this->waitingTime;
}

bool Game::hasStartingButtonBeenPressed() {
  return this->buttonsManager->hasAnyButtonBeenPressed() && this->buttonsManager->getPressedButtonIndex() == 0;
}

bool Game::isBallMovingTimeElapsed() {
  return (millis() - this->movingBallStartTimestamp) > this->gameData->ballMovingDuration;
}

bool Game::isStoppedBallWaitingTimeElapsed() {
  return (millis() - this->stoppedBallStartTimestamp) > this->gameData->stoppedBallTime;
}

bool Game::hasTimeBetweenBallMovingElapsed() {
  return (millis() - this->prevBallMovementTimestamp) > (1000 / this->gameData->ballMovingSpeed);
}

bool Game::hasUserPressedTheCorrectButton() {
  return this->buttonsManager->getPressedButtonIndex() == this->ballManager->getCurrentBallIndex();
}

////////////////////////////////////////////////////////////////////////////////
// States
////////////////////////////////////////////////////////////////////////////////

void Game::onWelcomeState() {
  Serial.println("Welcome to the Catch the Bouncing Led Ball Game. Press Key T1 to Start.");
  this->sleepWaitingStartTimestamp = millis();
  this->fadeManager->start();
  this->buttonsManager->start();
  this->changeState(WAITING);
}

void Game::onSleepState() {
  this->sleepManager->sleep();
  this->buttonsManager->start(); // re-enable buttons interrupts
  this->changeState(WELCOME);
}

void Game::onWaitingState() {
  this->fadeManager->fade();

  if (this->isWaitingTimeElapsed()) {
    Serial.println("Going to sleep...");
    delay(100);
    this->fadeManager->stopFade();
    this->changeState(SLEEP);
    return;
  }

  if (this->hasStartingButtonBeenPressed()) {
    this->fadeManager->stopFade();
    this->changeState(GAME_STARTING);
  }

  this->buttonsManager->releasePressedButton();
}

void Game::onGameStartingState() {
  this->gameData = new GameData({
    ballMovingSpeed: this->defaultBallMovingSpeed,
    ballMovingDuration : 0,
    stoppedBallTime : this->defaultStoppedBallTime,
    difficultyFactor : this->potentiometerManager->getDifficultyLevel(),
    score : 0
    });

  Serial.println("Difficulty level selected: " + String(this->gameData->difficultyFactor));
  Serial.println("GO!");
  this->changeState(ROUND_STARTING);
}

void Game::onRoundStartingState() {
  this->gameData->ballMovingDuration = this->minBallMovingTime + random(2000 + 1);
  this->movingBallStartTimestamp = millis();
  this->ballManager->start();
  this->changeState(MOVING_BALL);
}

void Game::onMovingBallState() {
  if (this->isBallMovingTimeElapsed()) {
    Serial.println("Ball stopped!");
    this->stoppedBallStartTimestamp = millis();
    this->buttonsManager->releasePressedButton();
    this->changeState(STOPPED_BALL);
  }
  else {
    if (this->hasTimeBetweenBallMovingElapsed()) {
      this->ballManager->nextBall();
      this->prevBallMovementTimestamp = millis();
    }
  }
}

void Game::onStoppedBallState() {
  if (this->isStoppedBallWaitingTimeElapsed()) {
    this->ballManager->stop();
    this->changeState(END_OF_GAME);
  }
  else {
    if (this->buttonsManager->hasAnyButtonBeenPressed()) {
      if (this->hasUserPressedTheCorrectButton()) {
        this->changeState(END_OF_ROUND);
      }
      else {
        this->changeState(END_OF_GAME);
      }
      this->ballManager->stop();
      this->buttonsManager->releasePressedButton();
    }
  }
}

void Game::onEndOfRoundState() {
  this->gameData->ballMovingSpeed *= (1.1 + (this->gameData->difficultyFactor / 4.0));
  this->gameData->stoppedBallTime /= (1.1 + (this->gameData->difficultyFactor / 4.0));
  this->gameData->score++;
  Serial.println("Score: " + String(this->gameData->score));
  Serial.println("Moving to next round...");
  this->changeState(ROUND_STARTING);
}

void Game::onEndOfGameState() {
  Serial.println("Game Over!");
  Serial.println("Your score is: " + String(this->gameData->score));
  this->buttonsManager->stop();
  this->changeState(WELCOME);
}