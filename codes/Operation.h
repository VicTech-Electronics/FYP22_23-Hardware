#include "Interface.h"
#include "Sense.h"
#include <EEPROM.h>

#define calibiration_resistor_value 1000

// Definition of pin connections
const uint8_t btn1_pin=2, btn2_pin=3, buzzer_pin=5, red_ind_pin=6, green_ind_pin=7, backlight_pin=A0, sense_pin=A1;

// Declaration of useful variables
bool measure, calibirate;
float proportionality_constant, moisture;
int pc_address = 0;

void startCalibiration(){
  digitalWrite(backlight_pin, HIGH);
  lcdPrint("Insert 100%", "Wet cashew nut");
  while(analogRead(sense_pin) == 0.0 || digitalRead(btn2_pin) == HIGH){ Serial.println("Wait for cashew nut for Calibiration");}

  lcdPrint("***", "Calibirating...");

  float res_cal_value = 0.0;
  float hum_cal_value = 0.0;
  float temp_cal_value = 0.0;

  for(int i=0; i<100; i++){
    float sense_voltage = analogRead(sense_pin) * 5/1023;
    res_cal_value += (5 * calibiration_resistor_value / sense_voltage) - calibiration_resistor_value;
    hum_cal_value += getTemperatureAndHumidity().humidity;
    temp_cal_value += getTemperatureAndHumidity().temperature;
    delay(30);
  }

  // get Calibiration value average
  res_cal_value /= 100;
  hum_cal_value /= 100;
  temp_cal_value /= 100;

  // Calculate proportionality constant
  proportionality_constant = (100 * temp_cal_value * res_cal_value) / hum_cal_value;
  EEPROM.put(pc_address, proportionality_constant);
  lcdPrint("Complete", "");
  calibirate = false;

  Serial.println("Resistance: " + String(res_cal_value));
  Serial.println("Humidity: " + String(hum_cal_value));
  Serial.println("Temperature: " + String(temp_cal_value));

  delay(2e3);
  digitalWrite(backlight_pin, LOW);
}

float getMoisturePercentage(){
  float resistance = (5 * calibiration_resistor_value / (analogRead(sense_pin) * 5/1023);
  if(((5 * calibiration_resistor_value / (analogRead(sense_pin) * 5/1023)) - calibiration_resistor_value) <= 0.0) return 100.0;
  else moisture = (proportionality_constant * getTemperatureAndHumidity().humidity) / (getTemperatureAndHumidity().temperature * resistance) * 100.0;
  Serial.println("Moisture: " + String(moisture));
  return moisture;
}