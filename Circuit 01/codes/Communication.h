#include <SoftwareSerial.h>
#include <NRFLite.h>
#include <SPI.h>
#define gsm_rx A2
#define gsm_tx A3

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
SoftwareSerial serialGSM(gsm_rx, gsm_tx);
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


void flushGSM(){
  while(serialGSM.available()){
    Serial.write(serialGSM.read());
    delay(50);
  }
}

void initializeGSM(){
  serialGSM.println("AT");
  delay(1e3);
  flushGSM();
  serialGSM.println("AT+CMGF=1");
  delay(1e3);
  flushGSM();
  serialGSM.println("AT+CNMI=1,2,0,0,0");
  delay(1e3);
  flushGSM();
}

void sendSMS(){
  serialGSM.println("AT+CMGS=\"" + phone_number + "\"");
  delay(1e3);
  flushGSM();
  serialGSM.println(message);
  delay(1e3);
  flushGSM();
  serialGSM.write(26);
  delay(1e3);
  flushGSM();
}
