#include "Communication.h"

// Definition of pin connection
const uint8_t buzzer_pin=9, indicator_pin=8, batter_level=A0;

// Method to calculate battery voltage
void checkPower(){
  float voltage = analogRead(batter_level);
  voltage = map(voltage, 0, 1023, 0, 100);

  if(voltage <= 75){
    digitalWrite(buzzer_pin, HIGH);
    digitalWrite(indicator_pin, HIGH);
  }else{
    digitalWrite(buzzer_pin, LOW);
    digitalWrite(indicator_pin, LOW);
  }
}

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(indicator_pin, OUTPUT);

  Serial.begin(9600);
  serialESP.begin(9600);
}

void loop() {
  checkPower();
  getLocation();
}
