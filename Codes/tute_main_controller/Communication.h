#include <SoftwareSerial.h>

// Definition of pin connection
const uint8_t buzzer_pin = 8;

SoftwareSerial serialESP(4, 2);

float latitude, longitude;
float latitudes[5] = {};
float longitudes[5] = {};

// Methode to get location informations data
void getLocation(){
  uint8_t index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}