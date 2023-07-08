#include <EEPROM.h>
#include "Communication.h"

// Definition of pin connections
const uint8_t touch_pin=A0, buzzer_pin=8, switch_pin=7, motor_pin=6;

// Decralation of usefull variables
const uint8_t password_address = 1, lock_address = 0;
float touch_calibiration_value, mini_accepted_value = 3;
String password, new_password;
bool lock_status, start=false;


bool isTouched(){
  float touch_value = analogRead(touch_pin);
  Serial.println("Touch value: " + String(touch_value));
  if(abs(touch_value - touch_calibiration_value) > mini_accepted_value) return true;
  else return false;
}

// Method to change password
void receiveCommand(){
  
  sms = receivedSMS();
  sms.trim();
  if(sms == password){
    Serial.println("Change state");
    start = !start;
    digitalWrite(buzzer_pin, HIGH);
    delay(1e3);
    digitalWrite(buzzer_pin, LOW);
  }else if(sms == "DATA"){
    getLocation();
    sendSMS(phone_number, "DATA => Lat: " + String(latitude) + ", Long: " + String(longitude));
  }else if(sms == "LOCK"){
    if(phone_number == owner_phone_number){
      lock_status = true;
      EEPROM.write(lock_address, lock_status);
      sendSMS(phone_number, "System LOCKED");
    }else{
      sendSMS(phone_number, "Sorry: You are not authorized!");
    }
  }else if(sms == "UNLOCK"){
    if(phone_number == owner_phone_number){
      lock_status = false;
      EEPROM.write(lock_address, lock_status);
      sendSMS(phone_number, "System UNLOCKED");
    }else{
      sendSMS(phone_number, "Sorry: You are not authorized!");
    }
  }else if(sms == "PASSWORD"){
    if(phone_number == owner_phone_number){
      sendSMS(owner_phone_number, "Enter New password");
      while(sms == ""){
        sms = receivedSMS();
      } // Wait for the password

      new_password = sms; sms="";
      sendSMS(owner_phone_number, "Confirm password");
      while(sms == ""){
        sms = receivedSMS();
      } // Wait for the password

      if(sms == new_password  && phone_number == owner_phone_number){
        sendSMS(owner_phone_number, "Password changed successful");

        // Write the string to EEPROM
        for (int i = 0; i < new_password.length(); i++) {
          EEPROM.write(password_address + i, new_password[i]);
        }
        EEPROM.write(password_address + new_password.length(), '\0');

        password = new_password;
      }else sendSMS(owner_phone_number, "Fail to change password");
    }else{
      sendSMS(phone_number, "Sorry: You are not authorized!");
    }
  }

  if(sms != "") delay(5e3);
}