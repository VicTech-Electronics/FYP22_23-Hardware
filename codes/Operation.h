#include "Interface.h"
#define OPEN true
#define CLOSE false

// Definition of pin connection
const uint8_t ph_pin=A5, valve_pin1=A3, valve_pin2=A4, pump1_pin=A1, pump2_pin=A2;

// Method to control solenoid valve
void valve(bool state){
  digitalWrite(valve_pin1, state);
  digitalWrite(valve_pin2, !state);
}

// Method to read PH value
float getPHValue() {
  float sensorValue = analogRead(ph_pin);
  float voltage = sensorValue * (5.0 / 1023.0);  // Convert the analog value to voltage
  float pH = 7 - (voltage - 2.5) * 3.0;  // Conversion formula based on the sensor characteristics
  return pH;
}

// Method to handle control operation
void operation(){
  if(getPHValue() <= 6.5){
    valve(CLOSE);
    digitalWrite(pump1_pin, HIGH);
    digitalWrite(pump2_pin, HIGH);
  }else{
    valve(OPEN);
    digitalWrite(pump1_pin, LOW);
    digitalWrite(pump2_pin, LOW);
  }
}