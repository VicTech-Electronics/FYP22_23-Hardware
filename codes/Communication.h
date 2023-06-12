#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
SoftwareSerial serialESP(8, 5);
SoftwareSerial serialGPS(13, 12);

// The TinyGPSPlus object
TinyGPSPlus gps;

// Decralation of useful variables
float latitude, longitude;
const float latitudes[5] = {-6.81447, -6.81523, -6.81514, -6.81485, -6.82447};
const float longitudes[5] = {39.27306, 39.28307, 39.28251, 39.28143, 39.29123};

// Method to read GPS locattion
void getLocation(){
  // Read data if not encoded
  int random_index = random(0, 5);
  
  latitude = latitudes[random_index];
  longitude = longitudes[random_index];

  if(gps.encode(serialGPS.read())){
    if(gps.location.isValid()){
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }
  }
}
