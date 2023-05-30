#include <SoftwareSerial.h>
#include <TinyGPSPlus.h>
#define GSM "gsm_serial"
#define GPS "gps_serial"
#define gps_rx 9
#define gps_tx 10
#define gsm_rx 11
#define gsm_tx 12


SoftwareSerial serialGSM(gsm_rx, gsm_tx);
SoftwareSerial serialGPS(gps_rx, gsm_tx);
TinyGPSPlus gps;

// Decralation of usefull variables
String latitude, longitude;
String sms, phone_number, owner_phone_number = "+255";

// Method to switch listening of softwareSerial
void serialListen(String serial_type){
  if(serial_type == GSM){
    serialGPS.stopListening();
    serialGSM.listen();
  }else if(serial_type == GPS){
    serialGPS.stopListening();
    serialGSM.listen();
  }
}

void flushGSM(){
  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(50);
  }
}


void initializeGSM(){
  serialGSM.println("AT+CMGF=1");
  delay(1e3);
  flushGSM();
  serialGSM.println("AT+CNMI=1,2,0,0,0");
  delay(1e3);
  flushGSM();
}

void sendSMS(String number, String message){
  serialGSM.println("AT+CMGS=\"" + number + "\"");
  delay(1e3);
  flushGSM();
  serialGSM.println(message);
  delay(1e3);
  flushGSM();
  serialGSM.write(26);
  delay(1e3);
  flushGSM();
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
    flushGSM();
  
    return sms;
  } return "";
}


// Method to get GPS location
void findLocation(){
  serialListen(GPS); delay(3e3);
  gps.encode(serialGPS.read());

  if(gps.location.isValid()){
    latitude = gps.location.lat();
    longitude = gps.location.lng();
  }else{
    latitude = "INVALID";
    longitude = "INVALID";
  }
}