/*
 * VicTech Electronics
 * Spona project
 * FYP2022/23
 */
 
#include "Operation.h"

// Decralation of usefull variable
boolean state;

// Method to handle alert Interrupt
void alerting(){
  state = !state;
  digitalWrite(ind_pin, state);
  digitalWrite(buzzer_pin, state);
  delayMicroseconds(15e3);
}

///////////////////// Default methods /////////////////////
void setup() {
  pinMode(ind_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialESP.begin(9600);
  serialGPS.begin(4800);
  
  pulseSensor.analogInput(hear_rate_pin);
  pulseSensor.setThreshold(550); // Adjust this value to your pulse sensor
  if(pulseSensor.begin())
    Serial.println("Fail to begin Heartbeat sensor");
 
  attachInterrupt(digitalPinToInterrupt(btn_pin), alerting, FALLING);
}

void loop() {
  operation();
}