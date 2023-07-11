/*
  VicTech Electronics
  Chibu circuit 1
  FYP2022/23
  VTE05
*/

#include "Operation.h"

// Definition of pin connection
const uint8_t btn1_pin=2, btn2_pin=3;

void setup() {
  pinMode(btn1_pin, INPUT_PULLUP);
  pinMode(btn2_pin, INPUT_PULLUP);

  SPI.begin();
  mfrc522.PCD_Init();
  Serial.begin(9600);

  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    // while (true); // Wait here forever.
  } radioData.FromRadioId = RADIO_ID;

  attachInterrupt(digitalPinToInterrupt(btn1_pin), confirmation, FALLING);
  attachInterrupt(digitalPinToInterrupt(btn2_pin), cancelation, FALLING);
}

void loop() {
  operation();
}