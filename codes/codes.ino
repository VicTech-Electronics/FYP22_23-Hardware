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

  Serial.begin(9600);

  servo.attach(servo_pin);
  servo.write(0);
  EEPROM.get(timeAddress, time);
  EEPROM.get(sizeAddress, size);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), settingsInterrupt, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), confirmationInterrupt, FALLING);
}

void loop() {
  operation();
}