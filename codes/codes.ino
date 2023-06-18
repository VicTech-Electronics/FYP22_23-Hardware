#include "Communication.h"

void setup() {
  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);

  Serial.begin(9600);
  serialESP.begin(9600);
  mod.begin(9600);
  dht.begin();
}
 
void loop() {
  sendToESP();
}
 
