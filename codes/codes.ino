#include "Operation.h"

void setup() {
  pinMode(laser_pin, OUTPUT);
  gate.attach(servo_pin); 
  digitalWrite(laser_pin, HIGH);
  calibration();
  Serial.begin(9600);
  serialESP.begin(9600);
}

void loop() {
  postData();
  receiveData();
}
