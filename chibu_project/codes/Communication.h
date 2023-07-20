#include "WString.h"
#include <stdint.h>
#include <SPI.h>
#include <MFRC522.h>
#include <NRFLite.h>
#include <SoftwareSerial.h>
#define esp_rx 5
#define esp_tx 4
#define SS_PIN 10
#define RST_PIN 9

const static uint8_t RADIO_ID = 1; 
const static uint8_t DESTINATION_RADIO_ID = 0; 
const static uint8_t PIN_RADIO_CE = 8;
const static uint8_t PIN_RADIO_CSN = 7;

struct RadioPacket{
    uint8_t FromRadioId;
    uint16_t passCode;
    char service;
};

NRFLite radio;
RadioPacket radioData;
MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial serialESP(esp_rx, esp_tx);


// Method to send data from NRF
void nrfSend(uint8_t code, char nrf_data){
  radioData.passCode = code;
  radioData.service = nrf_data;
  if (radio.send(DESTINATION_RADIO_ID, &radioData, sizeof(radioData)))
    Serial.println("NRF send data successful");
  else Serial.println("NRF fail to send data");
}

// Method to read card number from rfid card reader
String getCardNumber(){
  if (mfrc522.PICC_IsNewCardPresent()) {
    if (mfrc522.PICC_ReadCardSerial()) {
      String cardNumber = "";
      // Concatenate the UID bytes to form the card number
      for (byte i = 0; i < mfrc522.uid.size; i++) {
        cardNumber += mfrc522.uid.uidByte[i] < 0x10 ? "0" : "";
        cardNumber += String(mfrc522.uid.uidByte[i], HEX);
      }mfrc522.PICC_HaltA(); 
      return cardNumber;
    }return "";
  }return "";
}

// Method to send data to ESP module for IOT service
String espRequest(String esp_data){
  serialESP.println(esp_data);
  lcdPrint("Please wait...", "");

  while(!serialESP.available()){}; // Wait for response
  String esp_response = serialESP.readString();
  Serial.println("ESP response: " + esp_response);
  delay(2e3);
  return esp_response;
}