/*
  VicTech Electronics
  Saiwad Project 
  FYP2022/23
  VTE04
*/

#include "Service.h"
// Method to handle service request
void requestService(){
  if(is_port1 || is_port2 || is_port3){
    if(is_port1) available_port = 1;
    else if(is_port2) available_port = 2;
    else if(is_port3) available_port = 3;
    else available_port = 0;
  }

  service_required = true;
  delayMicroseconds(16e3);
}

void setup() {
  pinMode(port1_pin, OUTPUT);
  pinMode(port2_pin, OUTPUT);
  pinMode(port3_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(acceptor_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialGSM.begin(9600);
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(btn_pin), requestService, FALLING);

  // Welcome message
  lcdPrint("Welcome", "");
  lcdPrint("Mobile Phone", "Charging Machine");
  delay(1e3);

  digitalWrite(backlight_pin, HIGH);
}

void loop() {
  service();
  calculateChargingTime();
  lcdPrint("Mobile Phone", "Charging service");
  lcdPrint("Press button", "to get service");
  delay(3e3);
}
