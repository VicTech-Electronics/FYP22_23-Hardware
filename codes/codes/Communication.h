#include <SoftwareSerial.h>
#define esp_rx 5
#define esp_tx 6
#define gps_rx 18
#define gps_tx 19


// Decralation of useful variables
String data;

SoftwareSerial serialESP(esp_rx, esp_tx);
SoftwareSerial serialGPS(gps_rx, gps_tx);
SoftwareSerial serialBT(bluetooth_rx, bluetooth_tx);

String listenBT(){
  if(serialBT.available()){
    data = serialBT.readString();
    data.trim();
    return data;
  } return "none";
}
