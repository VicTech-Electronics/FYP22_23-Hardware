/*
  VicTech Electronics
  Godfrey Project
  FYP2022/23
  VTE13
*/

#include "Operation.h"

// Definition of pin connection
const uint8_t btn1_pin=2, btn2_pin=3;

// Method to handle Interrupt functions
void measure(){

}
void calibrate(){

}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(red_ind_pin, OUTPUT);
  pinMode(green_ind_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), measure, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), calibrate, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:

}
