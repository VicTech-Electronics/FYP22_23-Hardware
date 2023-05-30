/*
  VicTech Electronics
  Calista project
  FYP2022/23
  VTE10
*/
#include "Operation.h"

void setup() {
  pinMode(dir_pin, OUTPUT);
  pinMode(step_pin, OUTPUT);
  pinMode(motor_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(solenoid_pin, OUTPUT);
  pinMode(button_pin, INPUT_PULLUP);

  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(button_pin), requestStamping, FALLING);
}

void loop() {
  if(is_started) completeOperation();
}
