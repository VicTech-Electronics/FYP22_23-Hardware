#include <SoftwareSerial.h>
SoftwareSerial serialESP(8, 5);


// Decralation of useful variables
float latitude, longitude;
float latitudes[5] = {-6.81423, -6.81444, -6.81442, -6.81429, -6.81234};
float longitudes[5] = {39.28310, 39.28045, 39.28012, 39.28230, 39.28030};

// Method to read GPS locattion
void getLocation(){
  int index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}
