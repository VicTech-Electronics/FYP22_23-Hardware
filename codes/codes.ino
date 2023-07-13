#include "Operation.h"

void setup() {
  pinMode(valve_pin, OUTPUT);
  pinMode(flowrate_pin, INPUT);

  Serial.begin(9600);
  serialESP.begin(9600);
  EEPROM.get(units_address, units);

  lcd.init();
  lcd.backlight();
}

void loop() {
  operation();
}
