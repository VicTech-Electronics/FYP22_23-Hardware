/*
 * VicTech Electronics
 * Spona project
 * FYP2022/23
 */
#include "Operation.h"

// Decralation of usefull variable
boolean state;

// Method to handle alert Interrupt
void alerting(){
  state = !state;
  digitalWrite(ind_pin, state);
  digitalWrite(buzzer_pin, state);
  delayMicroseconds(15e3);
}


///////////////////// Default methods /////////////////////
void setup() {
  pinMode(ind_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialESP.begin(9600);
  attachInterrupt(digitalPinToInterrupt(btn_pin), alerting, FALLING);

  delay(10e3);
}

void loop() {
  operation();
  delay(5e3);
}

