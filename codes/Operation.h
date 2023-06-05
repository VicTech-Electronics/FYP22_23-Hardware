#include "Interface.h"
#include "Communication.h"

// Definition of pin connection
const uint8_t sensor1_pin=A3, sensor2_pin=A4, buzzer_pin=7, button_pin=3;

// Decralation of useful variables
bool alert, button false;
String location, phone_number="+255";

// Method to handle stop alert interrupt
void stopAlert(){
  alert = false;
  button = !button;
}

// Method to handle alert
void alerting(){
  if(alert) digitalWrite(buzzer_pin, HIGH);
  else digitalWrite(buzzer_pin, LOW);
}

// Method to handle all operations
void operaion(){
  
  if(digitalRead(sensor1_pin)==LOW){
    location = "Location A";
    alert = true;
  }else if(digitalRead(sensor2_pin) == LOW){
    location = "Location A";
    alert = true;
  }else alert = false;

  if(digitalRead(sensor1_pin)==LOW || digitalRead(sensor2_pin)==LOW){
    sendSMS(phone_number, "Falt detected at " + location);
    lcdPrint("Fault detected", "Area: " + location);
  }else lcdPrint("SAFE", "Transimition.");

  
  if(button);
  else alerting();
}