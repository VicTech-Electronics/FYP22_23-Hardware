/*
  VicTech Electronics
  Godfrey Project
  FYP2022/23
  VTE13
*/

#include "Operation.h"

// Decralation of useful variables
float temp, hum, moist;

// Method to handle Interrupt functions
void measurement(){
  measure = true;
}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(red_ind_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);

  Serial.begin(9600);
  dht.begin();
  lcd.begin(20, 4);

  lcdPrint("","Welcome", "", "", false); delay(1e3);
  lcdPrint("", "Cashewnut", "Meter", "", false); delay(2e3);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), measurement, FALLING);
}

void loop() {
  if(measure){
    delay(2e3);
    measure = false;
    while(!measure){
      Serial.println("In measurement mode");
      temp = getTemperatureAndHumidity().temperature;
      hum = getTemperatureAndHumidity().humidity;
      moist = getMoisturePercentage();
      digitalWrite(backlight_pin, HIGH);
      lcdPrint("MEASUREMENTS", "Moisture: " + String(moist) + "%", "Temp: " + String(temp), "Hum: " + String(hum), true);
      if(moist >= 30) alert(true);
      else alert(false);
      delay(1e3);
    }
    delay(2e3);
    measure = false;
  }else{
    lcdPrint("", "Cashewnut Moisture", "Digital meter", "", false);
    digitalWrite(backlight_pin, LOW);
    alert(false);
  }
}
