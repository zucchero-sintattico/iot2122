/**
 * Gruppo:
 *  - Alessandro Mazzoli
 *  - Manuel Andruccioli
 *  - Alex Testa
 */

#include <Arduino.h>
#include "game/game.h"

uint8_t potentiometerPin = A0;
uint8_t ballLedPins[4] = { 2, 3, 4, 5 };
uint8_t buttonPins[4] = { 6, 7, 8, 9 };
uint8_t fadingLedPin = 10;

Game* game = new Game(fadingLedPin, potentiometerPin, ballLedPins, buttonPins);

void setup() {
  Serial.begin(9600);
  game->setup();
}

void loop() {
  game->computeIteration();
}
