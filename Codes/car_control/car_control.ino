/*
  VicTech Electronics
  VictoniX final year project
  FYP2022/23
*/

#include "Control.h"

//////////// Default function ///////////////////
void setup() {
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(enabel_right,OUTPUT);
  pinMode(enabel_left, OUTPUT);

  Serial.begin(9600);
  serialBT.begin(9600);
  
  Serial.println("Program start");
}

void loop() { 
  motionControl();
}