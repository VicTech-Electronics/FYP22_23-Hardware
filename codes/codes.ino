/* 
  VicTech Electronics
  Rehema Project
  Mbegani (Diploma)
  FYP2022/23
  VTE34
*/
#include "Operation.h"

void setup() {
  pinMode(switch_pin, OUTPUT);
  pinMode(voltage_pin, INPUT);
  pinMode(backlight, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  servo.attach(servo_pin);
  servo.write(0);
  EEPROM.get(timeAddress, time);
  EEPROM.get(sizeAddress, size);

  digitalWrite(backlight, HIGH);
  lcdPrint("Welcome", ""); delay(3e3);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), settingsInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), confirmationInterrupt, FALLING);
}

void loop() {
  operation();
  changeOver();
}