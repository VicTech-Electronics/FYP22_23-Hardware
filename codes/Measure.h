#include "Arduino.h"
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>
#define tft_rx 12
#define tft_tx 11

SoftwareSerial serialTFT(tft_rx, tft_tx);
JSONVar json_object;

// Definition of pin connection
const uint8_t freq_pin=2, siginal_pin=A2, input_signal_pin=A4;

// Decralation of usefull variables
float frequency;
volatile unsigned long pulseWidth = 0;
volatile unsigned long lastCaptureTime = 0;

// Method to handle counting pulse Interrupt
void countPulse(){
  pulseWidth = micros() - lastCaptureTime;
  lastCaptureTime = micros();
}

// Method to measure frequency
float measureFrequence(){
  // Calculate frequency based on pulse width and time elapsed
  unsigned long currentTime = micros();
  unsigned long pulsePeriod = currentTime - lastCaptureTime;
  if (pulsePeriod > 0){
    return 1000000.0 / pulsePeriod;
  }else return -1;
}

// Method to measure signal
void measureSignal(){
  json_object["signal"] = float(analogRead(siginal_pin));
  json_object["frequence"] =  measureFrequence();

  String data = JSON.stringify(json_object);
  serialTFT.println(data);
}