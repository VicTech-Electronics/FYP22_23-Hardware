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
  pinMode(serial_listening_pin, INPUT);

  Serial.begin(9600);
  serial.begin(9600);
  serialBT.begin(9600);
  serialGPS.begin(9600);

  Serial.println("Program start");
}

void loop() { 
  if(digitalRead(serial_listening_pin) == HIGH) listeningToSerial();
  if(serial_listen) listenSerial();
  motionControl();
  delay(1e3);
}