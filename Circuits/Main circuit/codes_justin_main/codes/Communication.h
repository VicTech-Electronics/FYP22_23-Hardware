#include "SPI.h"
#include "NRFLite.h"
#include "Control.h"

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