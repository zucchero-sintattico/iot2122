#include <Arduino.h>
#include "game/game.h"

uint8_t potentiometerPin = A0;
uint8_t ballLedPins[4] = { 3, 5, 7, 9 };
uint8_t buttonPins[4] = { 2, 4, 6, 8 };
uint8_t fadingLedPin = 11;

Game* game = new Game(fadingLedPin, potentiometerPin, ballLedPins, buttonPins);

void setup() {
  Serial.begin(9600);
  game->setup();
}

void loop() {
  game->computeIteration();
}
