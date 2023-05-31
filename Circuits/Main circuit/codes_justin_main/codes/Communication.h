#include <stdint.h>
#include "SPI.h"
#include "NRFLite.h"
#include "Control.h"
#include <TinyGPS++.h>
#include <Arduino_JSON.h>
#define esp_rx 6
#define esp_tx 7

TinyGPSPlus gps;
JSONVar json_object;
SoftwareSerial serialESP(esp_rx, esp_tx);

// Definition of pin connection
const uint8_t buzzer_pin = A0;

const static uint8_t RADIO_ID = 0;       // Our radio's id.  The transmitter will send to this id.
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

struct RadioPacket{
  uint8_t FromRadioId;
  uint8_t data;
};

NRFLite radio;
RadioPacket radioData;

// Decralation of usefull variables
String vehicle_number = "T123-ABC";
float latitude, longitude;

// Method to receive data from NRF module
String nrfReceive(){
  while (radio.hasData()){
    radio.readData(&radioData);
    return String(radioData.data);
  } return "";
}

// Method to grab latitude and longitude
void trackLocation(){
  while (Serial.available() > 0) {
    if (gps.encode(Serial.read())) {
      if (gps.location.isValid()) {
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      }
    }
  }
}

// Method to send data
void sendData(){
  trackLocation();
  json_object["vehicle_number"] = vehicle_number;
  json_object["latitude"] = latitude;
  json_object["longitude"] = longitude;
  serialESP.println(JSON.stringify(json_object));
}