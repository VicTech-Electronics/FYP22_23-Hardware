#include <SoftwareSerial.h>

// Definition of pin connection
String data;
const uint8_t buzzer_pin = 8;

SoftwareSerial serialESP(4, 2);

float latitude, longitude;
float latitudes[5] = {-6.81434, -6.81433, -6.81352, -6.83425, -6.81235};
float longitudes[5] = {39.28033, 39.28450, 39.28022, 39.23750, 39.27053};

// Methode to get location informations data
void getLocation(){
  uint8_t index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}