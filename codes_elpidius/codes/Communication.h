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
String sms, phone_number, owner_phone_number = "+255787651007";

float latitudes[5] = {-6.81423, -6.81442, -6.81449, -6.81428, -6.81436};
float longitudes[5] = {39.28034, 39.28036, 39.28019, 39.28047, 39.28092};

void gsmCommand(String command){
  serialGSM.println(command);
  delay(1e3);

  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(50);
  }
}


void initializeGSM(){
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=1,2,0,0,0");
}

void sendSMS(String number, String message){
  gsmCommand("AT+CMGS=\"" + number + "\"");
  gsmCommand(message); delay(2e3);
  serialGSM.write(26);
  delay(1e3);
  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(50);
  }
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
    while(serialGSM.available()){
      Serial.write(serialGSM.read());
      delay(50);
    }
  
    return sms;
  } return "";
}


// Method to get GPS location
void getLocation(){
  int index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}