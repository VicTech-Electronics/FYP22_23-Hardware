#include <SoftwareSerial.h>
#define gsm_Rx 5
#define gsm_Tx 6

SoftwareSerial serialGSM(gsm_Rx, gsm_Tx);
String host = "http://161.35.210.153:5500";

// Decralation of useful variables
String sms, phone_number;
float latitude, longitude;
float latitudes[5] = {-6.80458, -6.80433, -6.80538, -6.80464, -6.80434};
float longitudes[5] = {39.23244, 39.22274, 39.22374, 39.22744, 39.24374};

// Method to get location 
void getLocation(){
  uint8_t index =random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}

// Method for gsm command
void commandGSM(String command) {
  serialGSM.println(command);
  delay(2e3); 
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initializeGSM(){
  commandGSM("AT");
  commandGSM("AT+CMGF=1");
  commandGSM("AT+CNMI=2,2,0,0,0");
}

void sendSMS(String phone, String message) {
  commandGSM("AT+CMGS=\"" + phone + "\"");
  commandGSM(message); delay(3e3);
  serialGSM.println(char(26));
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

String receiveSMS() {
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

// Methode to Connect GPRS connection
void connectGPRS(){
  commandGSM("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  commandGSM("AT+SAPBR=3,1,\"APN\",\"internet\"");
  commandGSM("AT+SAPBR=1,1");
  commandGSM("AT+SAPBR=2,1");
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
  commandGSM("AT+HTTPINIT");
  commandGSM("AT+HTTPPARA=\"CID\",1");
  commandGSM("AT+HTTPPARA=\"URL\",\"" + host + path + "\"");
  commandGSM("AT+HTTPPARA=\"CONTENT\",\"application/json\"");
  commandGSM("AT+HTTPDATA=" + String(json_data.length()) + ",100000");
  commandGSM(json_data);
  commandGSM("AT+HTTPACTION=1"); delay(20e3);
  commandGSM("AT+HTTPREAD"); delay(2e3);
  getResponse("+HTTPREAD:");
  commandGSM("AT+HTTPTERM");
}