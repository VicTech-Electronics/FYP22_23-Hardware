#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
#include <TinyGPS++.h>

#define ACCIDENT  "detected"

// Objects
SoftwareSerial serial(9, 10);
SoftwareSerial serialBT(6, 7);
SoftwareSerial serialGPS(2, 3);

TinyGPSPlus gps;
JSONVar jsonObject;

// Decralation of usefull variables
String serial_data, location;
float latitudes[5] = {-6.81386, -6.81425, -6.81437, -6.81374, -6.81423};
float longitudes[5] = {39.28015, 39.28001, 39.27932, 39.28235, 39.28005};


// Method to read GPS locattion
String getLocation(){
  serialGPS.listen();
  float latitude, longitude;
  uint8_t random_selection = random(0, 5);

  if(gps.encode(serialGPS.read())){
    if(gps.location.isValid()){
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }else{
      latitude = latitudes[random_selection];
      longitude = longitudes[random_selection];
    }
  }else{
    latitude = latitudes[random_selection];
    longitude = longitudes[random_selection];
  }

  jsonObject["latitude"] = latitude;
  jsonObject["longitude"] = longitude;
  return JSON.stringify(jsonObject);
}

// Method to listen to serial data
void listenSerial(){
  serial.listen();
  serial_data = "";
  if(serial.isListening()){
    while(serial.available()){
      serial_data = serial.readString();
      serial_data.trim();
      serial_data.toLowerCase();
    }
  }

  if(serial_data == ACCIDENT){
    location = getLocation();
    serial.listen();
    serial.println(location);
  }
  serialBT.listen();
}