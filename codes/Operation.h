#include <EEPROM.h>
#include "Interface.h"
#include "Measurement.h"
#include "Communication.h"
#include <Arduino_JSON.h>

// Pin connection
const uint8_t buzzer_pin = 11;

// Decralation of usefull variables
JSONVar json_object;
uint8_t unit_used_address=0;
float pressure_used, pressure_remain, total_pressure_used;
String json_string;
String device_id = "12345";

// Method to handle formationg Interrupt
void formatUsageISR(){
  total_pressure_used = 0.0;
  EEPROM.put(unit_used_address, total_pressure_used);
}

// Method to post data to webserver
String postData(String data_to_post, String purpose){
  String end_point;
  if(purpose == "usage") end_point = "/api/usage/";
  else end_point = "/api/notification/";
  postRequest(end_point, data_to_post);
  return "";
}

// Method to handle operation
void operation(){
  // Calculate data usage and post
  pressure_used = getPressureUsed();
  total_pressure_used += pressure_used;
  EEPROM.put(unit_used_address, total_pressure_used);

  json_object["device"] = device_id;
  json_object["units"] = pressure_used;
  json_string = JSON.stringify(json_object);

  String payload = postData(json_string, "usage");
  if(payload != "") pressure_remain = atof(payload.c_str());

  if(pressure_remain <= 0.0) digitalWrite(value_pin, LOW);
  else digitalWrite(value_pin, HIGH);
  
  lcdPrint("Gas meter", "Used: " + String(total_pressure_used) + " psi");
}
