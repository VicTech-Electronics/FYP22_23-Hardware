/*
 * Chuma circuit 01
 */
#include "Operation.h"

void setup() {
  // pinConfigurations
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(valve_pin1, OUTPUT);
  pinMode(valve_pin2, OUTPUT);
  pinMode(sensor1_pin, INPUT_PULLUP);
  pinMode(sensor2_pin, INPUT_PULLUP);

  // Initialize the objects
  Serial.begin(9600);
  serialGSM.begin(9600);
  initializeGSM();

  // Initialization of NRF communication module
  if (!radio.init(RADIO_ID, PIN_RADIO_CE, PIN_RADIO_CSN)){
    Serial.println("Cannot communicate with radio");
    while (true); // Wait here forever.
  }
  radioData.FromRadioId = RADIO_ID;
}

void loop() {
  operation();
}
