#include <SoftwareSerial.h>
#include <SoftwareSerial.h>
#define gsm_rx 10
#define gsm_tx 11

String phone_to_receive_sms = "+255626691059";

#define APN "internet" // APN of your GSM network provider
#define SERVER_ADDRESS "gee-fyp22-23.herokuapp.com" // HTTPS server address
#define SERVER_PORT 443 // HTTPS server port

SoftwareSerial serialGSM(gsm_rx, gsm_tx);

// Decralation of usefull variables
String gsm_data, phone_number, sms;
float latitude, longitude;
float latitudes[5] = {-6.81446, -6.82345, -6.81345, -6.83674, -6.81463};
float longitudes[5] = {39.28010, 39.27433, 39.28342, 39.26234, 39.28054};

// Method to flush Serial buffer
void gsmCommand(String command) {
  Serial.println(command);
  serialGSM.println(command); 
  delay(1e3);

  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

// Method to initialize GPRS connetion
// void intializeGPRS(){
//   gsmCommand("AT+CGATT=1");
//   gsmCommand("AT+SAPBR=3,1,\"CONTYPE\",\"GPRS\"");
//   gsmCommand("AT+SAPBR=3,1,\"APN\",\"" + String(APN) + "\"");
//   gsmCommand("AT+SAPBR=1,1");
//   gsmCommand("AT+HTTPINIT");
// }

// // Method to send POST request
// String postData(String end_point, String json_data){
//   // Set HTTP headers and payload
//   http.beginRequest();
//   http.post(end_point);
//   http.sendHeader("Content-Type", "application/json");
//   http.sendHeader("Content-Length", String(json_data.length()));
//   http.beginBody();
//   http.print(json_data);
//   http.endRequest();
//   // Check response
//   int statusCode = http.responseStatusCode();
//   String response = http.responseBody();
//   return response;
// }

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
  return sms;
}

// Method to check available call
void receiveCall(){
  // Extract caller's number
  button = false; delay(1e3);
  lcdPrint("Ringing...", "");

  bool accept_call_status = true;
  while(!button){
    Serial.println("Wait for call to receive");
  }
  if(button){
    gsmCommand("ATA");
  } 

  json_object["device"] = device_number;
  json_object["phone"] = phone_number;
  json_object["response"] = accept_call_status;

  String json_string = JSON.stringify(json_object);
}

// Method to get location from the GSP
void getLocation(){
  uint8_t index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}