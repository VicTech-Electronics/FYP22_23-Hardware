#include "Arduino.h"
// Decralation of usefull variables
String sms, phone_number;
String owner_phone = "+255689480093";

void gsmCommand(String command) {
  Serial.println(command);
  delay(1e3);

  while (Serial.available()) {
    Serial.write(Serial.read());
    delay(50);
  }
}

void initializeSMS() {
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=2,2,0,0,0");
}

void sendSMS(String phone, String message) {
  gsmCommand("AT+CMGS=\"" + phone + "\"");
  gsmCommand(message); delay(2e3);
  Serial.println(char(26));
  delay(1e3);
  while (Serial.available()) {
    Serial.write(Serial.read());
    delay(50);
  }
}
