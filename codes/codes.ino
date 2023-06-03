/*
  VicTech Electronics
  Denis Mvand Project
  DIT - Electrical (Diploma)
  FYP2022/23
*/

#include "Operation.h"

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(sensor1_pin, INPUT);
  pinMode(sensor2_pin, INPUT);
  pinMode(button_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialGSM.begin(9600);

  attachInterrupt(digitalPinToInterrupt(button_pin), stopAlert, FALLING);
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("Transimition", "Fault detector"); delay(3e3);
  intializeSMS();
}

void loop() {
  operaion();
}
