#include <EEPROM.h>
#include "Communication.h"

// Definition of pin connections
const uint8_t touch_pin=A0, buzzer_pin=8, switch_pin=7, motor_pin=6;

// Decralation of usefull variables
const uint8_t password_address = 0, lock_address = 1;
float touch_calibiration_value, mini_accepted_value = 10;
String password, new_password;
bool lock_status;

bool isTouched(){
  if(abs(analogRead(touch_pin) - touch_calibiration_value) > mini_accepted_value) return true;
  else return false;
}

// Method to handle password confirmation
void enterPassword(String phone){
  serialListen(GSM); sms="";
  sendSMS(phone, "Please Enter password");
  while(sms == ""){
    sms = receivedSMS();
  } // Wait for the password

  if(sms != password){
    sendSMS(phone, "Invalid password, Try again:");
    enterPassword(phone);
  }else sendSMS(phone, "Password success");
}

// Method to change password
void changePassword(){
  serialListen(GSM); 
  sms=receivedSMS();
  if(sms == password){
    sendSMS(owner_phone_number, "Enter New password");
    while(sms == ""){
      sms = receivedSMS();
    } // Wait for the password

    new_password = sms; sms="";
    sendSMS(owner_phone_number, "Confirm password");
    while(sms == ""){
      sms = receivedSMS();
    } // Wait for the password

    if(new_password == sms && phone_number == owner_phone_number){
      sendSMS(owner_phone_number, "Password changed successful");
      EEPROM.put(password_address, new_password);
      password = new_password;
    }else sendSMS(owner_phone_number, "Fail to change password"); 
  }else if(sms == "DATA"){
    findLocation();
    serialListen(GSM); 
    sendSMS(phone_number, "DATA => Lat: " + String(latitude) + ", Long: " + String(longitude));
  }else if(sms == "LOCK"){
    if(phone_number == owner_phone_number){
      lock_status = true;
      EEPROM.put(lock_address, lock_status);
      sendSMS(phone_number, "System LOCKED");
    }
  }
}