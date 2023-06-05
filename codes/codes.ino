/*
  VicTech Electronics
  Door pasword project
  FYP2022/23
  VTE
*/

#include "Operation.h"

void setup() {
  pinMode(buzzer_pin, OUTPUT);

  lcd.begin(16, 2);
  servo.attach(servo_pin);

  // Welcome message
  lcdPrint("Welcome", ""); delay(1e3);
  lcdPrint("Door password", "System"); delay(2e3);
}

void loop() {
  operation();
}
