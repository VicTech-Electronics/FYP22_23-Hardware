#include <HCSR04.h>
#define trig 12
#define echo 13
UltraSonicDistanceSensor ultrasonic(trig, echo);

// Definition of pin connection
const uint8_t flowrate_pin = 2;

// Decralation of usefull variables
float lenght = 10, width = 10, flowRate = 0.0;
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
    
    // Calculate flow rate
    flowRate = (float)flowCount / ((float)interval / 1000.0);
    
    Serial.print("Flow rate: ");
    Serial.print(flowRate);
    Serial.println(" L/min");
    
    flowCount = 0;
    previousTime = currentTime;
    
    interrupts();  // Enable interrupts

    return flowRate;
  } return -1;
}

float getVolumeDeplesion() { // Get deplesion volume in centimeter cube
  float height = 0.0;
  for(byte i=0; i<100; i++){
    height += ultrasonic.measureDistanceCm();
  } height /= 100;

  return lenght * width * height;
}
