#include <Arduino.h>
#include <EnableInterrupt.h>
#include <avr/sleep.h>

#include "config.h"

#include "program-data.h"
#include "game-config.h"
#include "game/game.h"

#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
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

uint8_t wakeUpPins[4] = {2, 3, 4, 5};
void setup() {
  Serial.begin(SERIAL_VELOCITY);
  SleepManager::setup(wakeUpPins);
  fadeManager->setup();
}

void loop() {
  Serial.println("Going to sleep");
  delay(500);
  SleepManager::sleep();
  Serial.println("Waked up");
}
