#include "Interface.h"
#include "Communication.h"

// Definition of pin connection
const uint8_t sensor1_pin=A3, sensor2_pin=A4, buzzer_pin=7;

// Decralation of useful variables
bool alert;
String location, phone_number="+255686715105";

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
    sendSMS(phone_number, "Fault detected at " + location);
    lcdPrint("Fault detected", "Area: " + location);
  }else lcdPrint("SAFE", "Transimition.");

  alerting();
}