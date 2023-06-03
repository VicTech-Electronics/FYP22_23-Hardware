#include <SoftwareSerial.h>
#define gsm_rx 5
#define gsm_tx 6

SoftwareSerial serialGSM(gsm_rx, gsm_tx);

// Method to send command to GSM
void gsmCommand(String command){
  serialGSM.println(command);
  delay(1e3);

  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(10);
  }
}

// Method to intialize SMS mode
void intializeSMS(){
  gsmCommand("AT");
  gsmCommand("AT+CMGF=1");
  gsmCommand("AT+CNMI=2,2,0,0,0");
}

// Method to sendSMS
void sendSMS(String phone, String message){
  gsmCommand("AT+CMGS=\"" + phone + "\"");
  gsmCommand(message);
  serialGSM.println(char(26));
}