#include "SPI.h"
#include "NRFLite.h"

const static uint8_t RADIO_ID = 0;
const static uint8_t PIN_RADIO_CE = 9;
const static uint8_t PIN_RADIO_CSN = 10;

struct RadioPacket{
  uint8_t FromRadioId;
  uint16_t passCode;
  char service;
};

NRFLite _radio;
RadioPacket _radioData;

// Definition of usefull variables
uint16_t password;
String required_service;

// Method to send NRF data
bool receiveData(){
  while (_radio.hasData()){
    _radio.readData(&_radioData);
    password = _radioData.passCode;
    required_service = String(_radioData.service);
    Serial.println("Data received");
    return true;
  } return false;
}