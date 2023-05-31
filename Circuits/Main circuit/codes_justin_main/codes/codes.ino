/*
  VicTech Electronics
  Justin circuit 1
  FYP2022/23
  FYP01
*/

#include "Communication.h"

void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(wheels_enable_pin, OUTPUT);
  
  Serial.begin(9600);
  serialBT.begin(9600);

  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    while (true); // Wait here forever.
  }
}

void loop() {
  if(nrfReceive() == "detected"){
    digitalWrite(buzzer_pin, HIGH);
    sendData(); delay(2e3);
    digitalWrite(buzzer_pin, LOW);
  }
  serialBluetoothReceive();
}
