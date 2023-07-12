/*
  VicTech Electronics
  Brian project
  FYP2022/23
  VTE27
*/

#include "Operation.h"

void setup() {
  pinMode(backlight, OUTPUT);
  pinMode(fan_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);  

  attachInterrupt(digitalPinToInterrupt(btn1_pin), confirmation, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), cancelation, FALLING);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  digitalWrite(backlight, HIGH);
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("DIT - Mechanical", "Project 2022/23"); delay(2e3);
}

void loop() {
  setting(); 
  lcdPrint("Electric Jack", "System"); 
}
