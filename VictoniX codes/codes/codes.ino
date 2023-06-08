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
  pinMode(buzzer_pin, OUTPUT);
  pinMode(brake_pin, INPUT);

  Serial.begin(9600);
  serial.begin(9600);
  serialESP.begin(9600);

  attachInterrupt(digitalPinToInterrupt(confirm_BTN), confirm, FALLING);
  attachInterrupt(digitalPinToInterrupt(cancel_BTN), cancel, FALLING);
}

void loop() {
  motionControl();
}
