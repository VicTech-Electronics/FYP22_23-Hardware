#include "Communication.h"
#include "Sense.h"
#include <Arduino_JSON.h>

// Definition of pin connection
const uint8_t ind_pin=9, btn_pin=2, buzzer_pin=10;

// Decralation of useful variable
String device_number = "12345";

// Method to create json variable
String locationJSON(float lt, float ln, float rate, float temp){
  JSONVar jsonObject;
  jsonObject["device_number"] = device_number;
  jsonObject["latitude"] = lt;
  jsonObject["longitude"] = ln;
  jsonObject["heart_rate"] = rate;
  jsonObject["body_temp"] = temp;
  return JSON.stringify(jsonObject);
}

// Methode that combine all operation of the system
void operation(){
  getLocation();
  serialESP.println(locationJSON(latitude, longitude, getHeartRate(), getTemperature()));
}
