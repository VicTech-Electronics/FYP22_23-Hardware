#include <SoftwareSerial.h>
#define gsm_rx 4
#define gsm_tx 3

SoftwareSerial serialGSM(gsm_rx, gsm_tx);

// Decralation of useful variables
String sms, phone_number, owner_phone_number = "+255626199010";

void flash_buffer() {
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initialize_sms() {
  serialGSM.println("AT"); // Attention
  delay(1e3);
  flash_buffer();
  serialGSM.println("AT+CMGF=1"); // Initialize sms mode
  delay(1e3);
  flash_buffer();
  serialGSM.println("AT+CNMI=2,2,0,0,0"); // Read sms directly
  delay(1e3);
  flash_buffer();
}

void send_sms(String phone, String message) {
  serialGSM.println("AT+CMGS=\"" + phone + "\"");
  delay(1e3);
  flash_buffer();
  serialGSM.println(message);
  delay(3e3);
  serialGSM.println(char(26));
  delay(1e3);
  flash_buffer();
}

String received_sms() {
  phone_number = "";
  while (serialGSM.available()) {
    sms = serialGSM.readString();
    phone_number = sms.substring(sms.indexOf("CMT") + 6, sms.indexOf("CMT") + 19);
    sms = sms.substring(sms.indexOf("CMT") + 46, sms.indexOf("CMT") + 100);
    sms.trim();
    sms.toUpperCase();
    Serial.println("SMS Received. \n SMS: " + sms);
    flash_buffer();
  
    return sms;
  } return "";
}