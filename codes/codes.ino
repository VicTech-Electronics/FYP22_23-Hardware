/*
  VicTech Electronics
  Gee Project
  FYP2022/23
  VTE06
*/
#include "Operation.h"

void setup() {
  pinMode(flowrate_pin, INPUT);
  pinMode(btn_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialGPS.begin(9600);
  serialGSM.begin(9600);

  attachInterrupt(digitalPinToInterrupt(btn_pin), listenBtn, FALLING);
  attachInterrupt(digitalPinToInterrupt(flowrate_pin), countPulse, RISING);
}

void loop() {

  // Listen to GSM
  while(serialGSM.available()){
    gsm_data = serialGSM.readString();
    gsm_data.trim();  
    gsm_data.toUpperCase();
    if(gsm_data.indexOf("RING") != -1) receiveCall();
    else receiveSMS();
  }
}
