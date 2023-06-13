/*
  VicTech Electronics
  Denis Mvand Project
  DIT - Electrical (Diploma)
  FYP2022/23
*/

#include "Operation.h"

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(sensor1_pin, INPUT);
  pinMode(sensor2_pin, INPUT);

  Serial.begin(9600);
  serialGSM.begin(9600);
  lcd.begin(16, 2);

  Serial.println("Project start");
  lcdPrint("Welcome", ""); delay(2e3);
  lcdPrint("Transimition", "Fault detector"); delay(2e3);
  lcdPrint("Intializing...", ""); delay(5e3);
  Serial.println("Initialize SMS mode");
  intializeSMS();
  Serial.println("DONE");

}

void loop() {
  operaion();
}
