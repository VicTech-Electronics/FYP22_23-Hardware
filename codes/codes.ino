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
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(button_pin), stopAlert, FALLING);
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("Transimition", "Fault detector");
  intializeSMS();
}

void loop() {
  operaion();
}
