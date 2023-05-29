/*
  VicTech Electronics
  Kitojo Project
  FYP2022/23
  VTE07
*/

#include "Measure.h"

// Definition of usefull variables
float default_input_signal, min_allowed_error = 10;

void setup() {
  pinMode(freq_pin, INPUT);
  serialTFT.begin(115200);
  
  // Calibirate default input signal
  default_input_signal = 0;
  for(byte i=0; i<100; i++) default_input_signal += analogRead(input_signal_pin);
  default_input_signal /= 100;
  attachInterrupt(digitalPinToInterrupt(freq_pin), countPulse, RISING);
}

void loop() {
  if(abs(analogRead(input_signal_pin) - default_input_signal) > min_allowed_error) measureSignal();
}
