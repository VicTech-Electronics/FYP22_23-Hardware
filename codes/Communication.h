#include <SoftwareSerial.h>
#include <Arduino_JSON.h>
#include <TinyGPS++.h>

SoftwareSerial serialESP(6, 5);
TinyGPSPlus gps;
JSONVar json_object;

// Decralation of latitudes and longitudes data of DIT
const float latitudes[5] = {-6.81440, -6.81442, -6.81445, -6.81447, -6.81449};
const float longitudes[5] = {39.28021, 39.28001, 39.28029, 39.28034, 39.28065};

// Decralation of usefull variables
float latitude, longitude;

// Methode to read GSP data
void getLocation() {
  int index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];

  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isValid()) {
        // Read latitude and longitude values
        float latitude = gps.location.lat();
        float longitude = gps.location.lng();
      }
    }
  }

  json_object["latitude"] = latitude;
  json_object["longitude"] = longitude;
  String json_string = JSON.stringify(json_object);
  serialESP.println(json_string);
}
