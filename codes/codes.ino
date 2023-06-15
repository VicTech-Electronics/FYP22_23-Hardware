#include "Operation.h"

void setup() {
  pinMode(laser_pin, OUTPUT);
  
  digitalWrite(laser_pin, HIGH);
  gate.attach(servo_pin); 
  gate.write(0);
  calibration();

  Serial.begin(9600);
  serialESP.begin(9600);

  Serial.println("Program start");
}

void loop() {
  postData();
  while(!serialESP.available());
  receiveData();
}
