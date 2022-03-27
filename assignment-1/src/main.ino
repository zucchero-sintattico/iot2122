#include <Arduino.h>

#include "config.h"

#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
#include "potentiometer/PotentiometerManager.h"
#include "ball/BallManager.h"

#include "game/game.h"

FadeManager* fadeManager = new FadeManager(9, 10, 5);
SleepManager* sleepManager = new SleepManager((uint8_t[4]) { 5, 6, 7, 8 });
PotentiometerManager* potentiometerManager = new PotentiometerManager(A0, 5);
BallManager* ballManager = new BallManager((uint8_t[4]) { 5, 6, 7, 8 });

Game* game = new Game(fadeManager, sleepManager, potentiometerManager, ballManager);

unsigned int prevOperationTimestamp;
float S = 1;

void setup() {
  Serial.begin(SERIAL_VELOCITY);
  game->setup();
  prevOperationTimestamp = millis();
}

void loop() {
  if (millis() - prevOperationTimestamp > 1000 / S) {
    ballManager->nextBall();
    prevOperationTimestamp = millis();
  }
}
