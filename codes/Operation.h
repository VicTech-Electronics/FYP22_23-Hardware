#include "Arduino.h"
#include "pins_arduino.h"
#include "ACS712.h"
#include "Communication.h"


// Definition of pin connection
const uint8_t ind1_pin=6, ind2_pin=7, 
              switch1_pin1=9, switch2_pin1=12,
              switch1_pin2=10, switch2_pin2=13,
              switch1_pin3=11, switch2_pin3=5,
              monitor_pin1=A1, monitor_pin2=A2,
              buzzer_pin=8, breaker_pin=3, voltage_pin=A5;

// Objects
ACS712_sensor sensor1(A3);
ACS712_sensor sensor2(A4);

// Decralation of usefull variables
float voltage, current1, current2;
bool current1_fault, current2_fault;
int reading_resistor=300000, divider_resistor=10000000;

// Method to handle switching signal
void switching(uint8_t channel, bool state){
  if(channel == 1){
    digitalWrite(ind1_pin, state);
    digitalWrite(switch1_pin1, state);
    digitalWrite(switch1_pin2, state);
    digitalWrite(switch1_pin3, state);
  }else if(channel == 2){
    digitalWrite(ind2_pin, state);
    digitalWrite(switch2_pin1, state);
    digitalWrite(switch2_pin2, state);
    digitalWrite(switch2_pin3, state);
  }
}

// Method to calculate the voltage of the circui
float getVoltage(){
  float reading = 0.0;
  for(byte i=0; i<100; i++){
    reading += analogRead(voltage_pin);
  }
  
  reading = reading / 100;
  reading = reading * (5./1023.); // Convert to voltage value
  reading = reading * 80;
  Serial.println("Reading: " + String(reading));
  return 220;
}

// Method to handle the whole system operation
void operation(){
  voltage = getVoltage();
  current1 = sensor1.get_Irms();
  current2 = sensor2.get_Irms();

  Serial.println("Voltage: " + String(voltage));
  Serial.println("Current1: " + String(current1));
  Serial.println("Current2: " + String(current2));

  // if(current1 > 2){
  //   switching(1, false);
  //   current1_fault = true;
  //   digitalWrite(buzzer_pin, HIGH);
  //   sendSMS(owner_phone, "Overcurrent detected at channel 1");
  // }
  // if(current2 > 3){
  //   switching(2, false);
  //   current2_fault = true;
  //   digitalWrite(buzzer_pin, HIGH);
  //   sendSMS(owner_phone, "Overcurrent detected at channel 2");
  // }

  if(voltage <= 190){
    switching(1, false);
    switching(2, false);
    digitalWrite(buzzer_pin, HIGH);
    sendSMS(owner_phone, "Undervoltage detected");
  }else if(voltage >= 240.0){
    switching(1, false);
    switching(2, false);
    digitalWrite(buzzer_pin, HIGH);
    sendSMS(owner_phone, "Over voltage detected");
  }else{
    switching(1, true);
    switching(2, true);
  }

  // Switch buzzer OFF in no warning
  if(current1 <= 2 && current2 <= 3 && voltage > 190 && voltage < 240)
    digitalWrite(buzzer_pin, LOW);

  // Reset
  if(current1_fault){
    float expected_current;
    float reading = analogRead(monitor_pin1);
    reading = reading * (5./1023.); // Convert reading to voltage reading
    reading = (reading*10e3) / (5 - reading); // Read the resistance value

    expected_current = voltage / reading;
    if(expected_current <= 2){
      switching(1, true);
      current1_fault = false;
    }
  }


  if(current2_fault){
    float expected_current;
    float reading = analogRead(monitor_pin2);
    reading = reading * (5./1023.); // Convert reading to voltage reading
    reading = (reading*10e3) / (5 - reading); // Read the resistance value

    expected_current = voltage / reading;
    if(expected_current <= 2){
      switching(2, true);
      current2_fault = false;
    }
  }

}