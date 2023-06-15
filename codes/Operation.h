#include "Sense.h"
#include <Servo.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

Servo gate;
JSONVar json_received_object, json_post_object;
SoftwareSerial serialESP(11, 10);

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
  json_post_object["slot1Status"] = packingStatus[0];
  json_post_object["slot2Status"] = packingStatus[1];
  json_post_object["slot3Status"] = packingStatus[2];
  String data_to_post = JSON.stringify(json_post_object);
  serialESP.println(json_post_object);

  Serial.println("POST: " + data_to_post);
}

// MNethod to open the gate
void openGate(){
  Serial.println("Open the gate");
  for(byte i=0; i<=90; i++){
    gate.write(i);
    delay(20);
  }
  delay(5e3);
  for(byte i=90; i>=0; i--){
    gate.write(0);
    delay(20);
  }
}

// Method read data
String receiveData(){
  payload = serialESP.readString();
  payload.trim();
  Serial.println("Data received: " + payload);
  if(payload.indexOf("SUCCESS") == -1 && payload.indexOf("FAIL") == -1){
    Serial.println("ACTION");
    json_received_object = JSON.parse(payload);
    if((int)json_received_object["packing"] == 1)
      if(analogRead(sensorPins[0]) < calibirationValues) openGate();
    if((int)json_received_object["payment"] == 1)
      if(analogRead(sensorPins[1]) < calibirationValues) openGate();
  }
}