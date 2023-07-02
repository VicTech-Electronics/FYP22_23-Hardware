#include <SPI.h>
#include <MFRC522.h>
#include <SoftwareSerial.h>
#define SS_PIN 8
#define RST_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
SoftwareSerial serialESP(5, 10);

// Decralation of usefull variable
String card_number;

// Method to read card number
String getCardNumber(){
  // Check if a new card is present
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()){
    // Get the card number
    card_number = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      card_number += String(mfrc522.uid.uidByte[i], HEX);
    }
    Serial.println("Card Number: " + card_number);

    // Halt PICC and stop reading
    mfrc522.PICC_HaltA();
    mfrc522.PCD_StopCrypto1();

    return card_number;
  } return "";
}