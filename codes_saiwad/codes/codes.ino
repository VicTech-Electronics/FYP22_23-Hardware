/*
  VicTech Electronics
  Saiwad Project 
  FYP2022/23
  VTE04
*/

#include "Service.h"

void setup() {
  pinMode(port1_pin, OUTPUT);
  pinMode(port2_pin, OUTPUT);
  pinMode(port3_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(acceptor_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialGSM.begin(9600);
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(acceptor_pin), coutingPulseISR, FALLING);

  // Welcome message
  lcdPrint("Welcome", "");
  lcdPrint("Mobile Phone", "Charging Machine");
  delay(1e3);

  digitalWrite(backlight_pin, HIGH);
}

void loop() {
  service();
  calculateChargingTime();
  lcdPrint("Mobile Phone", "Charging service");
  lcdPrint("Press button", "to get service");
  delay(3e3);
}
