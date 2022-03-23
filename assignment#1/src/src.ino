#include "potentiometer.h"
#include "fade.h"
#include "sleep.h"

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), wakeUp, RISING);
}

void loop() {
  fade();
  sleep();
}

void wakeUp(){
  Serial.println("Ciao mi sono svegliato");
}
