/*
  VicTech Electronics
  Likulike project
  FYP2022/23
  VTE51
*/

#include "Operation.h"

void setup() {
  pinMode(value_pin, OUTPUT);

  lcd.init();
  lcd.backlight();

  lcdPrint("Welcome", ""); delay(1e3);
  lcdPrint("Gas Vending", "System"); delay(2e3);

  // Calculate Intital pressure
  initial_pressure = 0.0;
  for(byte i=0; i<100; i++)
    initial_pressure += getPressure();
  initial_pressure /= 100;
}

void loop() {
  operation();
}
