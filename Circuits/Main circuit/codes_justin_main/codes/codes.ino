/*
  VicTech Electronics
  Justin circuit 1
  FYP2022/23
  FYP01
*/

#include "Communication.h"

void setup() {
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(enabel, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  
  Serial.begin(9600);
  serialBT.begin(9600);

  // if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
  //   Serial.println("Cannot communicate with radio");
  //   while (true); // Wait here forever.
  // }
}

void loop() {
  bluetooth_data = listenBT();
  motionControl(bluetooth_data);
  if(nrfReceive() == "detected"){
    digitalWrite(buzzer_pin, HIGH);
    // sendData();
    delay(2e3);
    digitalWrite(buzzer_pin, LOW);
  }
}
