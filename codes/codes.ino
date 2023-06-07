#include <SoftwareSerial.h>
#define esp_rx 10
#define esp_tx 11
SoftwareSerial serialESP(esp_rx, esp_tx);

// Definition of pin connection
const uint8_t ind_pin=7, switch_pin=A0;

// Decralation of useful variables
bool state;
String esp_serial_data;

void setup() {
  pinMode(ind_pin, OUTPUT);
  pinMode(switch_pin, OUTPUT);

  Serial.begin(9600);
  serialESP.begin(9600);
}

void loop() {
  while(!serialESP.available());
  esp_serial_data = serialESP.readString();
  esp_serial_data.trim();
  esp_serial_data.toUpperCase();

  if(esp_serial_data == "ON") state = true;
  else state = false;

  digitalWrite(ind_pin, state);
  digitalWrite(switch_pin, state);

  Serial.println("Data received: " + esp_serial_data);
}
