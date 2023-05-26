#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
SoftwareSerial serialESP(8, 5);
SoftwareSerial serialGPS(13, 12);

// The TinyGPSPlus object
TinyGPSPlus gps;

// Decralation of useful variables
float latitude, longitude;

// Method to read GPS locattion
void getLocation(){
  if(gps.encode(serialGPS.read())){
    if(gps.location.isValid()){
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }else{
      Serial.println("Invalid GSP location");
      latitude = -1;
      longitude = -1;
    }
  }else{
    Serial.println("Fail to decode NEMA sentense");
    latitude = -1;
    longitude = -1;
  }
}
