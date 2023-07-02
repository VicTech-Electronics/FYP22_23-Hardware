#include <SoftwareSerial.h>
SoftwareSerial serialGSM(9, 10);

// Server connection data
String host = "https://likulike-fyp22-23-0a6c988d5ed9.herokuapp.com";

// Decralation of usefull variables
String phone_number, sms;

void gsmCommand(String command) {
  serialGSM.println(command);
  delay(1e3);

  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
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
  serialGSM.println(message);
  delay(3e3);
  serialGSM.println(char(26));
  delay(1e3);

  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

String receivedSMS() {
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

// Methode to Connect GPRS connection
void connectGPRS(){
  gsmCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  gsmCommand("AT+SAPBR=3,1,\"APN\",\"internet\"");
  gsmCommand("AT+SAPBR=1,1");
  gsmCommand("AT+SAPBR=2,1");
  gsmCommand("AT+HTTPINIT");
  gsmCommand("AT+HTTPSSL=1");
}


// Methode to get response from the Server
void getResponse(String res_command){
  String payload;
  if(serialGSM.available()) payload = serialGSM.readString();
  payload = payload.substring(payload.indexOf(res_command)+13, payload.indexOf(res_command)+20);
  payload.trim();
  Serial.println("Payload: " + payload);
}

// Methode to send HTTP request
void postRequest(String path, String json_data){
  Serial.println("Data: " + json_data); delay(1e3);
  gsmCommand("AT+HTTPPARA=\"CID\",1");
  gsmCommand("AT+HTTPPARA=\"URL\",\"" + host + path + "\"");
  gsmCommand("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  gsmCommand("AT+HTTPDATA=" + String(json_data.length()) + ",100000");
  gsmCommand(json_data);
  gsmCommand("AT+HTTPACTION=1"); delay(20e3);
  gsmCommand("AT+HTTPREAD"); delay(2e3);
  getResponse("+HTTPREAD:");
  gsmCommand("AT+HTTPTERM");
}