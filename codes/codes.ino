/*
  VicTech Electronics
  Kitojo Project
  FYP2022/23
  VTE07
*/

#include "Measure.h"

// Definition of usefull variable
String serial_data = "pause";

// Definition of usefull variables
float default_input_signal;

void setup() {
  pinMode(freq_pin, INPUT);
  serialTFT.begin(9600);
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(freq_pin), countPulse, RISING);
  Serial.println("Start");
}

void loop() {

  if(serialTFT.available()){
    serial_data = "";
    delay(50);
    while(serialTFT.available()){
      serial_data += char(serialTFT.read());
    }
  }
  
  if(serial_data == "play"){
    Serial.println("In play");
    siginalProcesing();
    Serial.read();
  } 
}
