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
  serialGSM.begin(9600);
  serialGPS.begin(9600);

  delay(5e3);
  // Method to calibirate touch sensor
  touch_calibiration_value = 0.0;
  for(int i=0; i<100; i++) touch_calibiration_value += analogRead(touch_pin);
  touch_calibiration_value /= 100;

  Serial.println("Calibiration: " + String(touch_calibiration_value));

  EEPROM.get(password_address, password);
  EEPROM.get(lock_address, lock_status);

  /*
    Procedure to follow
    power system start without password
    power of motorvehicle start depends on system password
    system can be off while rider complete process of switching the vehicle and riding

    NOTE: Switching system
  */
}

void loop(){
  changePassword();

  if(isTouched()){
    digitalWrite(buzzer_pin, HIGH);
    sendSMS(owner_phone_number, "Your bike is touch, Please take action");
  }else digitalWrite(buzzer_pin, LOW);

  if(!lock_status && digitalRead(switch_pin) == LOW) digitalWrite(motor_pin, HIGH);
  else digitalWrite(motor_pin, LOW);
}