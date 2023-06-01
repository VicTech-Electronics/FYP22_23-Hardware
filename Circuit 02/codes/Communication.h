#include <NRFLite.h>
#include <SPI.h>

// Definition of usefull terms
const static uint8_t RADIO_ID = 5;
const static uint8_t DESTINATION_RADIO_ID = 7;
const static uint8_t PIN_RADIO_CE = 10;
const static uint8_t PIN_RADIO_CSN = 8;

// Decralation of packet to send
struct RadioPacket{
    uint8_t FromRadioId;
    char message;
};

// Initilization of objects
NRFLite radio;
RadioPacket radioData;

// Methode to send NRF data
String receiveNRF(char radio_message){
  while (radio.hasData()){
    radio.readData(&radioData);

    if(radioData.FromRadioId == DESTINATION_RADIO_ID){
      if(radioData.message == 'X') return "Empty";
      else if(radioData.message == 'Y') return "Full";
      else return "None";
    } return "None";
  } return "None";
}
