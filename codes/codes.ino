/*
  VicTech Electronics
  Gee Project
  FYP2022/23
  VTE06
*/
#include "Operation.h"

void setup() {
  pinMode(flowrate_pin, INPUT);
  pinMode(button_pin, INPUT_PULLUP);
  Serial.begin(9600);
  serialGSM.begin(9600);

  lcd.begin(16, 2);
  lcdPrint("Fuel tank", "Security System");
  lcdPrint("Initializing...", ""); delay(10e3);
  
  initializeSMS();
  connectGPRS();
  initial_volume = getVolume();

  lcdPrint("Done", "");

  attachInterrupt(digitalPinToInterrupt(button_pin), listenBtn, FALLING);
  attachInterrupt(digitalPinToInterrupt(flowrate_pin), countPulse, RISING);
}

void loop() {
  operation();
}
