#include "Interface.h"
#include "Sense.h"
#include <EEPROM.h>

#define calibiration_resistor_value 5000

// Definition of pin connections
const uint8_t btn1_pin=2, buzzer_pin=5, red_ind_pin=6, backlight_pin=A0, sense_pin=A1;

// Declaration of useful variables
bool measure;
float  moisture;

// Method to 
void alert(bool state){
  if(state){
    digitalWrite(red_ind_pin, HIGH);
    digitalWrite(buzzer_pin, HIGH);
  }else{
    digitalWrite(red_ind_pin, LOW);
    digitalWrite(buzzer_pin, LOW);
  }
}

float getMoisturePercentage(){
  float sense_reading = analogRead(sense_pin);
  return map(sense_reading, 0, 1023, 0, 100);
}
