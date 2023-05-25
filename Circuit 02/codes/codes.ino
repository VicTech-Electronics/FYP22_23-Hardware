/*
 *  Chuma circuit 2
 */

#include "Communication.h"
#include "Operation.h"

void setup() {
  pinMode(pump1_pin, OUTPUT);
  pinMode(pump2_pin, OUTPUT);
  pinMode(sensor_pin, INPUT_PULLUP);
  
  // Initialization of NRF communication module
  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    while (true); // Wait here forever.
  }
}

void loop() {
  operation();
}
