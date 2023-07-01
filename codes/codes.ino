#include "Communication.h"
#include <Arduino_JSON.h>

// Decralation of usefull variables
JSONVar json_object;
String device_number = "DEV000GH";
String end_point = "/api/v1/pet-location";

void setup() {
  Serial.begin(9600);
  serialGSM.begin(9600);
  
  commandGSM("AT+CFUN=1,1"); // Reset GSM
  Serial.println("Waiting...");
  delay(5e3);
  Serial.println("Done");

  initializeGSM();
  connectGPRS();
}

void loop() {
  getLocation();
  json_object["device_number"] = device_number;
  json_object["latitudes"] = latitude;
  json_object["longitudes"] = longitude;
  String data = JSON.stringify(json_object);

  postRequest(end_point, data);
  delay(3e3);

  if(alert){
    sendSMS("+255689361469", "Sorry Owner, your pet is outside the geofence!");
    alert = false;
  }
}