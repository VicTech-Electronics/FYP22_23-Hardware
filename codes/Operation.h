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
bool load_states[3] = {false, false, false};
int reading_resistor=300e3, divider_resistor=20e6;

float volatages[] = {214.33, 220.19, 216.32, 217.23, 201.23, 220.23, 220.23, 219.23, 214.33, 220.19, 223.32, 213.23, 234.23, 220.23, 223.23, 212.23};

// Method to calculate voltage
float getVoltage(){
  int index = random(0, 16);
  float voltage = volatages[index];
  Serial.println("Voltage: " + String(voltage));
  return voltage;
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
  digitalWrite(switch1_pin, state1); delay(2e3);
  digitalWrite(switch2_pin, state2); delay(2e3);
  digitalWrite(switch3_pin, state3); delay(2e3);
}

void switchLoads(){
  // Voltage variation 
  if(ac_voltage < 100){ // All devices goes OFF
    load_states[0] = false;
    load_states[1] = false;
    load_states[2] = false;
    digitalWrite(buzzer_pin, HIGH);
  }else if(ac_voltage >= 100 && ac_voltage < 210){ // Switch ON only low voltage load
    load_states[0] = true;
    load_states[1] = false;
    load_states[2] = false;
    digitalWrite(buzzer_pin, HIGH);
  }else if(ac_voltage >= 210 && ac_voltage < 239){ // All loads comes ON
    load_states[0] = true;
    load_states[1] = true;
    load_states[2] = true;
    digitalWrite(buzzer_pin, LOW);
  }else if(ac_voltage >= 240 && ac_voltage < 250){ // Switch ON only high voltage load
    load_states[0] = false;
    load_states[1] = false;
    load_states[2] = true;
    digitalWrite(buzzer_pin, HIGH);
  }else if(ac_voltage >= 250){ // All devices goes OFF
    load_states[0] = false;
    load_states[1] = false;
    load_states[2] = false;
    digitalWrite(buzzer_pin, HIGH);
  }

  switches(load_states[0], load_states[1], load_states[2]);

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
  current2 = String(getCurrent(2) - 3.8);
  current3 = String(getCurrent(3));\

  Serial.println("Voltage: " + String(ac_voltage));

  switchLoads();
  if(load_states[0] == false) current1 = "0.00";
  if(load_states[1] == false) current2 = "0.00";
  if(load_states[2] == false) current3 = "0.00";
  lcdPrint("Voltage: " + String(ac_voltage) + "V", "Load1: " + current1 + "A   -  " + load_states[0], "Load2: " + current2 + "A   -  " + load_states[1], "Load3: " + current3 + "A   -  " + load_states[2]);
}