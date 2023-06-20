/*
  VicTech Electronics
  Elpidius Project
  FYP2022/23
  VTE
*/

#include "Operation.h"

//////////////////// Default Methods ////////////////////
void setup(){
  pinMode(motor_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(switch_pin, INPUT_PULLUP);
  
  Serial.begin(9600);
  serialGPS.begin(9600);
  serialGSM.begin(9600);
  
  delay(5e3);
  // Method to calibirate touch sensor
  touch_calibiration_value = 0.0;
  for(int i=0; i<100; i++) touch_calibiration_value += analogRead(touch_pin);
  touch_calibiration_value /= 100;

  Serial.println("Calibiration: " + String(touch_calibiration_value));
  
  lock_status = EEPROM.read(lock_address);
  char reading_char = EEPROM.read(password_address);
  int i=0;
  while(reading_char != '\0'){
    password += reading_char;
    i++;
    reading_char = EEPROM.read(password_address + i);
  } password.trim();

  Serial.println("Password: " + password);
  Serial.println("Lock: " + String(lock_status));
  initializeGSM();
}

void loop(){
  receiveCommand();
  if(!lock_status){
    if(start) digitalWrite(motor_pin, HIGH);
    else digitalWrite(motor_pin, LOW);
  }else{
    if(isTouched()){
      delay(1e3);
      if(!serialGSM.available()){
        digitalWrite(buzzer_pin, HIGH);
        sendSMS(owner_phone_number, "Your bike is touch, Please take action");
      }
    }else digitalWrite(buzzer_pin, LOW);
  }
}