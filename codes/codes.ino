/*
  VicTech Electronics
  Jesca Project
  FYP2022/23
  VTE03
*/

#include "Operation.h"

void setup() {
  pinMode(dir1_pin, OUTPUT);
  pinMode(dir2_pin, OUTPUT);
  pinMode(step1_pin, OUTPUT);
  pinMode(step2_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  Serial.begin(9600);
  SPI.begin(); 
  mfrc522.PCD_Init();

  lcd.init();
  lcd.backlight();

  // set Motor directions
  digitalWrite(dir1_pin, HIGH);
  digitalWrite(dir2_pin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(btn1_pin), confirmation, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn1_pin), cancelation, FALLING);
}

void loop() {
  lcdPrint("PAD Vanding", "Machine");
  // if(confirm) service();
  service();
  delay(1e3);
}
