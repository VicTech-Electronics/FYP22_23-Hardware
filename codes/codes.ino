/*
  VicTech Electronics
  Brian project
  FYP2022/23
  VTE27
*/

#include "Operation.h"

void setup() {
  pinMode(fan_pin, OUTPUT);
  pinMode(backlight, OUTPUT);
  pinMode(peltier_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), confirmation, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), cancelation, FALLING);

  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("Thermal Electric", "Peltier vaccine");

  while(!confirm){
    lcdPrint("Please", "Balance temp.");
    delay(1e3);
  }
}

void loop() {
  setting();
  operation();
}
