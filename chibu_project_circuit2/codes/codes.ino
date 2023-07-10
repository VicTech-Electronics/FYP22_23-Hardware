#include "Operation.h"

void setup() { 
  pinMode(door1_pin, OUTPUT);
  pinMode(door2_pin, OUTPUT);
  pinMode(led1_pin, OUTPUT);
  pinMode(led2_pin, OUTPUT);

  Serial.begin(9600);

  // put your setup code here, to run once:
  if (!_radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    while (1); // Wait here forever.
  }
}

void loop() {
  operation();
}
