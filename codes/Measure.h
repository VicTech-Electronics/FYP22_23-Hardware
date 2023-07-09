#include "Communication.h"

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
void siginalProcesing(){
  float  peak_value=0.0;
  for(byte i=0; i<100; i++){
    float frequence = measureFrequence();
    int signal = map(analogRead(siginal_pin), 0, 1023, 0, 255);
    Serial.println("Signal: " + String(signal));

    if(signal > peak_value) peak_value = signal;

    String frequence_data = "t0.txt=\"Feq: " + String(frequence) + "Hz\"";
    String siginal_data = "add 1,0," + String(signal);

    Serial.println("Siginal " + String(siginal_data));
    
    sendData(frequence_data);
    sendData(siginal_data);
  }
  peak_value = map(peak_value, 0, 255, 0, 12);
  String peak_data = "t1.txt=\"Peak: " + String(peak_value) + "V\"";
  sendData(peak_data);
  
}