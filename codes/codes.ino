#include "Operations.h"

void setup() {
  lcd.init();
  lcd.backlight();
  rfid.PCD_Init();
  servo1.attach(5);
  servo2.attach(6);
  servo1.write(0);
  servo2.write(0);
  Serial.begin(9600);

  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(btn1_pin), doorBtnISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), gateBtnISR, FALLING);
}

void loop() {
  operation();
}
