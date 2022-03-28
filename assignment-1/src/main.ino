#include <Arduino.h>
#include "game/game.h"
///////////////////////////////////////////////////////////////////////////////
// Configuration
///////////////////////////////////////////////////////////////////////////////

uint8_t potentiometerPin = A0;
uint8_t ballLedPins[4] = { 2, 3, 4, 5 };
uint8_t buttonPins[4] = { 6, 7, 8, 9 };
uint8_t fadingLedPin = 10;

///////////////////////////////////////////////////////////////////////////////
// Game creation
///////////////////////////////////////////////////////////////////////////////
Game* game = new Game(fadingLedPin, potentiometerPin, ballLedPins, buttonPins);

void setup() {
  Serial.begin(9600);
  game->setup();
}

unsigned long lastIterationTimestamp = 0;

void loop() {
  game->computeIteration();
}
