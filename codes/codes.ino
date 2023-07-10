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
  lcdPrint("Electric Jack", "System"); delay(2e3);

  while(!confirm){
    lcdPrint("Please", "Customize height");
    delay(1e3);
  }
}

void loop() {
  setting(); 
}
