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
  Serial.println("Done");
}

void loop() {
  count_rate++;
  if(count_rate<=30 && pulse_counter>1) service();
  calculateChargingTime();

  if(available_port > 0)
    lcdPrint("Mobile Phone", "Charging service");
  else lcdPrint("No service", "Ports are full");
}
