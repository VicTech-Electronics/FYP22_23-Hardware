#include <SoftwareSerial.h>
#include <NRFLite.h>
#include <SPI.h>

// Definition of usefull terms
const static uint8_t RADIO_ID = 7;
const static uint8_t DESTINATION_RADIO_ID = 5;
const static uint8_t PIN_RADIO_CE = 10;
const static uint8_t PIN_RADIO_CSN = 9;

// Decralation of packet to send
struct RadioPacket{
    uint8_t FromRadioId;
    char message;
};

// Initilization of objects
SoftwareSerial serialGSM(A4, A5);
NRFLite radio;
RadioPacket radioData;


// Declaration of usefull variables and constants
String phone_number = "+255716515333";
String message = "Hello maintanance department, Go and check the system";


// Methode to send NRF data
void sendNRF(char radio_message){
  radioData.message = radio_message;
  if (radio.send(DESTINATION_RADIO_ID, &radioData, sizeof(radioData)))
    Serial.println("NRF transimision success");
  else
    Serial.println("NRF fail to transimit");
}


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

void sendSMS(){
  gsmCommand("AT+CMGS=\"" + phone_number + "\"");
  gsmCommand(message);
  serialGSM.write(26);
  delay(1e3);
}
