#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#define gps_rx 8
#define gps_tx 9
#define gsm_rx 10
#define gsm_tx 11

TinyGPSPlus gps;
SoftwareSerial serialGSM(gsm_rx, gsm_tx);
SoftwareSerial serialGPS(gps_rx, gps_tx);

// Decralation of usefull variables
String gsm_data, phone_number, sms;
float latitude, longitude;

// Method to flush Serial buffer
void flashBuffer() {
  while (serialGSM.available()) {
    Serial.write(serialGSM.read());
    delay(50);
  }
}

// Method to initialize sms mode
void initializeSMS() {
  serialGSM.println("AT"); // Attention
  delay(1e3); flashBuffer();
  serialGSM.println("AT+CMGF=1"); // Initialize sms mode
  delay(1e3); flashBuffer();
  serialGSM.println("AT+CNMI=2,2,0,0,0"); // Read sms directly
  delay(1e3); flashBuffer();
}

// Method to send sms
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

// Method to receive sms
String receiveSMS() {
  phone_number = sms.substring(sms.indexOf("CMT") + 6, sms.indexOf("CMT") + 19);
  sms = sms.substring(sms.indexOf("CMT") + 46, sms.indexOf("CMT") + 100);
  Serial.println("SMS Received. \n SMS: " + sms);
  flashBuffer();
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

  while(!button){
    // Check if "NO CARRIER" response is received
    if (serialGSM.find("NO CARRIER")) {
      lcdPrint("Hangup", "");
      button = true;
    }
  } button = false;
}

// Method to get location from the GSP
void getLocation(){
  while (serialGPS.available()) {
    char c = serialGPS.read();      // Read GPS data character by character
    if (gps.encode(c)) {
      if (gps.location.isValid()){
        latitude = gps.location.lat();
        longitude = gps.location.lng();
      }
    }
  }
}