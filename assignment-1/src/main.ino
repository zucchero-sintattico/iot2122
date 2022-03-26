#include <Arduino.h>

#include "config.h"

#include "program-data.h"
#include "game-config.h"
#include "game/game.h"

#include "fade/FadeManager.h"

/*
ProgramConfig programConfig = {
  serialBaudRate: 9600
};

GameConfig gameConfig = {
  potentiometerPin: A0,
  
  fadePin: A1,
  fadeInterval: 1000,
  
  buttonsCount: 4,
  baseButtonPin: 2,
  
  secondsToSleep: 10
};

GameData gameData = {
  S: 0,
  T1: 0,
  T2: 0,
  Score: 0,
  currentGameState: WAITING
};

Game *game = new Game(gameData);
*/

FadeManager *fadeManager = new FadeManager(9, 10, 5);

void setup() {
  Serial.begin(9600);
  fadeManager->setup();
}

void loop() {
  fadeManager->fade();
}
