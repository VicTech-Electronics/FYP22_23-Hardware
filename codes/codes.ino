/*
  VicTech Electronics
  Chuga Project
  FYP2022/23
  VTE__
*/

#include "Operation.h"

// Definition of pin connection
const uint8_t btn_pin=2;

// Decralation of useful variables
boolean active;

// Methode to handle interrupt
void activation(){
  active = !active;
  delayMicroseconds(16e3);
}

void setup() {
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);
  pinMode(valve_pin1, OUTPUT);
  pinMode(valve_pin2, OUTPUT);

  lcd.begin(20, 4);

  lcdPrint("", "Welcome", "", ""); delay(1e3);
  lcdPrint("", "Water monitoring", "System", ""); delay(2e3);

  attachInterrupt(digitalPinToInterrupt(btn_pin), activation, FALLING);
}

void loop() {
  if(active) operation();
  else lcdPrint("","System", "DEACTIVATED", "");
}
