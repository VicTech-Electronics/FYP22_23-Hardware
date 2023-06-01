#include "Sense.h"
#include <Servo.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

Servo gate;
JSONVar jsonObject;
SoftwareSerial serialESP(10, 11);

// Defintion of pin connections
const uint8_t laser_pin=8, servo_pin=3;

// Decralation of useful variables
String payload;

// Method to read packing status
void checkPacking(){
  for(byte i=0; i<3; i++){
    getSensor();
    if(analogRead(sensorPins[i+2]) < calibirationValues[i+2])
      packingStatus[i+2] = true;
    else packingStatus[i+2] = false;
  }
}

// Method for posting slot status
void postData(){
  jsonObject["slot1Status"] = packingStatus[0];
  jsonObject["slot2Status"] = packingStatus[1];
  jsonObject["slot3Status"] = packingStatus[2];
  serialESP.println(JSON.stringify(jsonObject));
}

// MNethod to open the gate
void openGate(){
  gate.write(90);
  delay(10);
  gate.write(0);
}

// Method read data
String receiveData(){
  payload = serialESP.readString();
  jsonObject = JSON.parse(payload);

  if((int)jsonObject["packing"] == 1)
    if(analogRead(sensorPins[0]) < calibirationValues) openGate();
  if((int)jsonObject["payment"] == 1)
    if(analogRead(sensorPins[1]) < calibirationValues) openGate();
}