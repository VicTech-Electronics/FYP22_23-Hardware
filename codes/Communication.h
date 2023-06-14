#define TINY_GSM_MODEM_SIM800 // Define the modem model you are using

#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include <TinyGsmClient.h>
#include <ArduinoHttpClient.h>
#include <SoftwareSerial.h>
#define gps_rx 8
#define gps_tx 9
#define gsm_rx 10
#define gsm_tx 11

String phone_to_receive_sms = "+255626691059";

#define APN "internet" // APN of your GSM network provider
#define SERVER_ADDRESS "gee-fyp22-23.herokuapp.com" // HTTPS server address
#define SERVER_PORT 443 // HTTPS server port

TinyGPSPlus gps;
SoftwareSerial serialGPS(gps_rx, gps_tx);
SoftwareSerial serialGSM(gsm_rx, gsm_tx);
TinyGsm modem(serialGSM);
TinyGsmClient gsmClient(modem);
HttpClient http(gsmClient, SERVER_ADDRESS, SERVER_PORT);

// Decralation of usefull variables
String gsm_data, phone_number, sms;
float latitude, longitude;
float latitudes[5] = {-6.81446, -6.82345, -6.81345, -6.83674, -6.81463};
float longitudes[5] = {39.28010, 39.27433, 39.28342, 39.26234, 39.28054};

// Method to flush Serial buffer
void gsmCommand(String command) {
  serialGSM.println(command); 
  delay(1e3);
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

// Method to initialize GPRS connetion
void intializeGPRS(){
  gsmCommand("AT+CGATT=1");
  gsmCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
  gsmCommand("AT+SAPBR=3,1,\"APN\",\"" + String(APN) + "\"");
  gsmCommand("AT+SAPBR=1,1");
  gsmCommand("AT+HTTPINIT");
}

// Method to send POST request
String postData(String end_point, String json_data){
  // Set HTTP headers and payload
  http.beginRequest();
  http.post(end_point);
  http.sendHeader("Content-Type", "application/json");
  http.sendHeader("Content-Length", String(json_data.length()));
  http.beginBody();
  http.print(json_data);
  http.endRequest();
  // Check response
  int statusCode = http.responseStatusCode();
  String response = http.responseBody();
  return response;
}

// Method to initialize sms mode
void initializeSMS() {
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=2,2,0,0,0");
}

// Method to send sms
void sendSMS(String message) {
  gsmCommand("AT+CMGS=\"" + phone_to_receive_sms + "\"");
  gsmCommand(message);
  serialGSM.println(char(26));
  delay(1e3);
}

// Method to receive sms
String receiveSMS(){
  phone_number = gsm_data.substring(sms.indexOf("CMT") + 6, gsm_data.indexOf("CMT") + 19);
  sms = gsm_data.substring(sms.indexOf("CMT") + 46, gsm_data.indexOf("CMT") + 100);
  Serial.println("SMS Received. \n SMS: " + sms);

  json_object["device"] = device_number;
  json_object["phone"] = phone_number;
  json_object["content"] = sms;

  String json_string = JSON.stringify(json_object);
  postData("/api/message/", json_string);
  return sms;
}

// Method to check available call
void receiveCall(){
  // Extract caller's number
  int index1 = gsm_data.indexOf("\"");
  int index2 = gsm_data.indexOf("\"", index1 + 1);
  if (index1 != -1 && index2 != -1)
    phone_number = gsm_data.substring(index1 + 1, index2);
  lcdPrint("Ringing...", phone_number);


  bool accept_call_status = true;
  while(!button){
    // Check if "NO CARRIER" response is received
    if (serialGSM.find("NO CARRIER")) {
      lcdPrint("Hangup", "");
      button = true;
      accept_call_status = false;
    }
  } button = false;


  json_object["device"] = device_number;
  json_object["phone"] = phone_number;
  json_object["response"] = accept_call_status;

  String json_string = JSON.stringify(json_object);
  postData("/api/call/", json_string);
}

// Method to get location from the GSP
void getLocation(){
  uint8_t index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];

  serialGPS.listen(); delay(1e3);
  if(gps.encode(serialGPS.read())){
    if (gps.location.isValid()){
      latitude = gps.location.lat();
      longitude = gps.location.lng();
    }
  }
}