#include <HCSR04.h>
UltraSonicDistanceSensor ultrasonic(12, 13);

// Definition of pin connection
const uint8_t flowrate_pin = 3;

// Decralation of usefull variables
float flowRate = 0.0;
volatile int flowCount = 0;
unsigned long currentTime;
unsigned long previousTime = 0;
unsigned long interval = 1000;  // Measurement interval in milliseconds


// Method to handle count pulse Interrupt
void countPulse() {
  flowCount++;
}

float getFlowRate(){
  currentTime = millis();
  if (currentTime - previousTime >= interval) {
    noInterrupts();  // Disable interrupts
    flowRate = (float)flowCount / ((float)interval / 1000.0);
    flowCount = 0;
    previousTime = currentTime;
    interrupts();  // Enable interrupt
  }
  return flowRate;
}

float getVolume(){ // Get deplesion volume in centimeter cube
  float height = 0.0;
  for(byte i=0; i<100; i++){
    height += ultrasonic.measureDistanceCm();
  } height /= 100;

  return 1017.36 * height;
}
