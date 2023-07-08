#include "Arduino.h"
#include <stdint.h>
#include "Interface.h"
#include "ACS712.h"

// Definition of pin connection
const uint8_t buzzer_pin=4, voltage_pin=A1,
              btn1_pin=0, btn2_pin=1, btn3_pin=3, 
              switch1_pin=5, switch2_pin=6, switch3_pin=7;

// Decralation of useful variables
float ac_voltage;
String current1, current2, current3;
int reading_resistor=130e3, divider_resistor=6.2e6;

// Method to calculate voltage
float getVoltage(){
  float reading = analogRead(voltage_pin);
  float voltage = reading * (5./1023.);
  voltage = (voltage * (reading_resistor + divider_resistor)) / reading_resistor;
  return voltage / sqrt(2);
}

// Method to calculate current
float getCurrent(uint8_t sensor_number){
  Serial.println("In function");
  uint8_t pin;
  if(sensor_number == 1) pin = A3;
  else if(sensor_number == 2) pin = A4;
  else if(sensor_number == 3) pin = A5;

  float current = 0.0;
  ACS712_sensor currentSensor(pin);
  for(byte i=0; i<2; i++){
    Serial.println("In loop");
    current += currentSensor.get_Irms();
  } current /= 2;

  Serial.print("Current: ");
  Serial.println(current, 8);

  return current;
}


// Method to handle condition for switching loads
void switches(bool state1, bool state2, bool state3){
  digitalWrite(switch1_pin, state1);
  digitalWrite(switch2_pin, state2);
  digitalWrite(switch3_pin, state3);
}

void switchLoads(){

  // Voltage variation 
 
  if(ac_voltage < 100){ // All devices goes OFF
    switches(false, false, false);
  }else if(ac_voltage >= 100 && ac_voltage < 210){ // Switch ON only low voltage load
    switches(true, false, false);
  }else if(ac_voltage >= 210 && ac_voltage < 239){ // All loads comes ON
    switches(true, true, true);
  }else if(ac_voltage >= 240 && ac_voltage < 250){ // Switch ON only high voltage load
    switches(false, false, true);
  }else if(ac_voltage >= 250){ // All devices goes OFF
    switches(false, false, false);
  }




  // if(current1.toInt() > 2 || ac_voltage < 207 || ac_voltage > 265){
  //   digitalWrite(switch1_pin, LOW);
  //   digitalWrite(buzzer_pin, HIGH);
  //   current1 = "--";
  // }
  // if(current2.toInt() > 4 || ac_voltage < 207 || ac_voltage > 252){
  //   digitalWrite(switch2_pin, LOW);
  //   digitalWrite(buzzer_pin, HIGH);
  //   current2 = "--";
  // }
  // if(current3.toInt() > 4 || ac_voltage < 100 || ac_voltage > 252){
  //   digitalWrite(switch3_pin, LOW);
  //   digitalWrite(buzzer_pin, HIGH);
  //   current3 = "--";
  // }


  // Button reset system codes
  if(digitalRead(btn1_pin) == LOW){
    digitalWrite(switch1_pin, HIGH);
    digitalWrite(buzzer_pin, LOW);
  }
  if(digitalRead(btn2_pin) == LOW){
    digitalWrite(switch2_pin, HIGH);
    digitalWrite(buzzer_pin, LOW);
  }
  if(digitalRead(btn3_pin) == LOW){
    digitalWrite(switch3_pin, HIGH);
    digitalWrite(buzzer_pin, LOW);
  }
}

// Method for the system operations
void Operation(){
  ac_voltage = getVoltage();
  current1 = String(getCurrent(1));
  current2 = String(getCurrent(2));
  current3 = String(getCurrent(3));

  switchLoads();
  lcdPrint("Voltage: " + String(ac_voltage) + "V", "Load 1: " + current1 + "A", "Load 2: " + current2 + "A", "Load 3: " + current3 + "A");
}