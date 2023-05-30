#include <SoftwareSerial.h>
#define gsm_rx 9
#define gsm_tx 10

SoftwareSerial serialGSM(gsm_rx, gsm_tx);

// Decralation of usefull variables
String phone_number, sms;

void flashBuffer() {
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initializeSMS() {
  serialGSM.println("AT"); // Attention
  delay(1e3);
  flashBuffer();
  serialGSM.println("AT+CMGF=1"); // Initialize sms mode
  delay(1e3);
  flashBuffer();
  serialGSM.println("AT+CNMI=2,2,0,0,0"); // Read sms directly
  delay(1e3);
  flashBuffer();
}

void sendSMS(String phone, String message) {
  serialGSM.println("AT+CMGS=\"" + phone + "\"");
  delay(1e3);
  flashBuffer();
  serialGSM.println(message);
  delay(3e3);
  serialGSM.println(char(26));
  delay(1e3);
  flashBuffer();
}

String receivedSMS() {
  Serial.println("In received sms function");
  while (serialGSM.available()) {
    sms = serialGSM.readString();
    phone_number = sms.substring(sms.indexOf("CMT") + 6, sms.indexOf("CMT") + 19);
    sms = sms.substring(sms.indexOf("CMT") + 46, sms.indexOf("CMT") + 100);
    sms.trim();
    sms.toUpperCase();
    Serial.println("SMS Received. \n SMS: " + sms);
    flashBuffer();
  
    return sms;
  } return "";
}