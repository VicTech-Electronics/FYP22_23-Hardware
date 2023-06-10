#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
#include <TinyGPS++.h>

#define ACCIDENT  "detected"

// Definition of pin connection
const uint8_t serial_listening_pin = 2;

// Objects
SoftwareSerial serial(9, 10);
SoftwareSerial serialBT(6, 7);
SoftwareSerial serialGPS(2, 3);

TinyGPSPlus gps;
JSONVar jsonObject;

// Decralation of usefull variables
bool serial_listen;
String serial_data, location;
float latitudes[5] = {-6.81386, -6.81425, -6.81437, -6.81374, -6.81423};
float longitudes[5] = {39.28015, 39.28001, 39.27932, 39.28235, 39.28005};


// Method to read GPS locattion
String getLocation(){
  float latitude, longitude;
  uint8_t random_selection = random(0, 5);

  serialGPS.listen(); delay(1e3);
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

  serial.listen();
  jsonObject["latitude"] = latitude;
  jsonObject["longitude"] = longitude;
  return JSON.stringify(jsonObject);
}

// Method to listen to serial data
void listenSerial(){
  serial_data = "";
  Serial.println("In serial listening");
  while(!serial.available()){
    Serial.println("Wait for serial data");
    delay(1e3);
  } // Wait for the data
  serial_data = serial.readString();
  serial_data.trim();
  serial_data.toLowerCase();
  Serial.println("serial data: " + serial_data);

  if(serial_data == ACCIDENT){
    location = getLocation();
    Serial.println("Location: " + location);
    serial.println(location);
  }

  serial_listen = false;
}

// Method to handle Interrupt
void listeningToSerial(){
  Serial.println("Enterrupted");
  serial.listen();
  if(serial.isListening()){
    Serial.println("Listening");
    serial.println("listening");
    serial_listen = true;
  }
}