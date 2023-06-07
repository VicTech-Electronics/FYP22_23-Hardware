/*
  VicTech Electronics
  VictoniX final year project
  FYP2022/23
*/

#include "Control.h"

//////////// Default function ///////////////////
void setup() {
  pinMode(enabel_right,OUTPUT);
  pinMode(enabel_left, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);

  serial.begin(9600);
  Serial.begin(9600);
  serialBT.begin(9600);
  serialGPS.begin(9600);

  Serial.println("Program start");
}

void loop() {
  motionControl();
  listenSerial();
  delay(100);
}
