#include <Arduino.h>

#include "config.h"
#include "fade/FadeManager.h"
#include "sleep/SleepManager.h"
#include "potentiometer/PotentiometerManager.h"

#include "game/game.h"

FadeManager *fadeManager = new FadeManager(9, 10, 5);
SleepManager *sleepManager = new SleepManager((uint8_t[4]){5, 6, 7, 8});
PotentiometerManager *potentiometerManager = new PotentiometerManager(A0, 5);

Game *game = new Game(fadeManager, sleepManager, potentiometerManager);

void setup() {
  Serial.begin(SERIAL_VELOCITY);
  game->setup();
}

void loop() {
  Serial.println(potentiometerManager->readPotentiometer());
  delay(200);
}
