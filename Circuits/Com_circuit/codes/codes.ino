/*
  VicTech Electronics
  Justin circuit 2
  FYP2022/23
  VTE01
*/

#include "SPI.h"
#include "NRFLite.h"

const static uint8_t RADIO_ID = 1;             // Our radio's id.
const static uint8_t DESTINATION_RADIO_ID = 0; // Id of the radio we will transmit to.
const static uint8_t PIN_RADIO_CE = 10;
const static uint8_t PIN_RADIO_CSN = 8;

struct RadioPacket{
  uint8_t from_radioID;
  uint8_t data;
};

NRFLite radio;
RadioPacket radioData;

// Method to send Info
void nrfTransmit(){
  radioData.data = 1;
  if (radio.send(DESTINATION_RADIO_ID, &radioData, sizeof(radioData)))
    Serial.println("Success");
  else Serial.println("Failed");
}

void setup() {
  Serial.begin(9600);

  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    while (true); // Wait here forever.
  } radioData.from_radioID = RADIO_ID;
}


void loop() {
  if(Serial.available())
    if(Serial.readString() == "detected")
      nrfTransmit();
}
