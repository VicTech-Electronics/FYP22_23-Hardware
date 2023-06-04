/* 
  VicTech Electronics
  Frolian Project
  Diploma - DIT (Biomedical)
  FYP2022/23
*/

#include "Operation.h"

void setup() {
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(backlight, OUTPUT);
  pinMode(motor_pin, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  // Welcome message
  digitalWrite(backlight, HIGH);
  lcdPrint("Welcome", ""); delay(1e3);
  lcdPrint("Heartrate", "Monitoring"); delay(1e3);
}

void loop() {
  operation();
}
