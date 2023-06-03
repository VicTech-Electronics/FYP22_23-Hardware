/*
 * VicTech Electronics
 * VictoniX project
 * FYP2022/23
 * VTE__
 */

# include "Function.h"


void setup() {
  pinMode(confirm_BTN, INPUT_PULLUP);
  pinMode(cancel_BTN, INPUT_PULLUP);
  pinMode(indicator_pin, OUTPUT);
  pinMode(enabel_right,OUTPUT);
  pinMode(enabel_left, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(brake_pin, INPUT);

  Serial.begin(9600);
  serialBT.begin(9600);
  serialGPS.begin(9600);

  attachInterrupt(digitalPinToInterrupt(confirm_BTN), confirm, FALLING);
  attachInterrupt(digitalPinToInterrupt(cancel_BTN), cancel, FALLING);
}

void loop() {
  motionControl();
}
