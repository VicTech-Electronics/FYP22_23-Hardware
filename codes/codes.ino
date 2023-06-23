#include "Operation.h"

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(switch1_pin, OUTPUT);
  pinMode(switch2_pin, OUTPUT);
  pinMode(switch3_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);
  pinMode(btn3_pin, INPUT_PULLUP);


  Serial.begin(9600);
  lcd.begin(20, 4);

  lcdPrint("", "Welcome", "", ""); delay(2e3);
  lcdPrint("", "Automatic protection", "System", ""); delay(2e3);
  lcdPrint("", "Initializing...", "", "");
}

void loop() {
  Operation();
}
