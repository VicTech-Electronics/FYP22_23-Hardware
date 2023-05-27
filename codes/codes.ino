/*
  VicTech Electronics
  Godfrey Project
  FYP2022/23
  VTE13
*/

#include "Operation.h"

// Method to handle Interrupt functions
void measurement(){
  measure = !measure;
  delayMicroseconds(16e3);
}
void calibiration(){
  calibirate = true;
}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(red_ind_pin, OUTPUT);
  pinMode(green_ind_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  Serial.begin(9600);
  dht.begin();

  attachInterrupt(digitalPinToInterrupt(btn1_pin), measurement, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), calibiration, FALLING);

  // get proportionality constant for the last calibiration
  EEPROM.get(pc_address, proportionality_constant);
}

void loop() {
  if(calibirate) startCalibiration();
  if(measure){
    Serial.println("In measurement mode");
    lcdPrint("Moisture: " + String(getMoisturePercentage()) + "%", "T: " + String(getTemperatureAndHumidity().temperature) + "  H: " + String(getTemperatureAndHumidity().humidity));
  }else{
    lcdPrint("Cashew nut", "Moisture sensor");
  }
}
