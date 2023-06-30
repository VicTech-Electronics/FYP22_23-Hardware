#include <SoftwareSerial.h>
SoftwareSerial serialGSM(3, 4);

// Decralation of useful variables
String sms, phone_number, phone = "+255717935070";

void gsmCommand(String command) {
  serialGSM.println(command);
  delay(1e3);

  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initialize_sms() {
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=2,2,0,0,0");
}

void send_sms(String phone_to_receive, String message_to_send) {
  gsmCommand("AT+CMGS=\"" + phone_to_receive + "\"");
  gsmCommand(message_to_send); delay(3e3);
  serialGSM.println(char(26));
  delay(1e3);
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

String received_sms() {
  Serial.println("In received sms function");
  while (serialGSM.available()) {
    sms = serialGSM.readString();
    phone_number = sms.substring(sms.indexOf("CMT") + 6, sms.indexOf("CMT") + 19);
    sms = sms.substring(sms.indexOf("CMT") + 46, sms.indexOf("CMT") + 100);
    sms.trim();
    sms.toUpperCase();
    Serial.println("SMS Received. \n SMS: " + sms);
    return sms;
  } return "";
}