#include "Sensor.h"
#include <Servo.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

Servo gate;
SoftwareSerial serialESP(11, 10);

// Defintion of pin connections
const uint8_t servo_pin=8;

// Decralation of useful variables
String payload;

// Sensor objects
Sensor exit_gate(A0);
Sensor entry_gate(A4);
Sensor slot1(A3);
Sensor slot2(A1);
Sensor slot3(A2);


// Decralation of usefull variables
bool slot1_status; float slot1_calibiration_value;
bool slot2_status; float slot2_calibiration_value;
bool slot3_status; float slot3_calibiration_value;
bool exit_status; float exit_calibiration_value;
bool entry_status; float entry_calibiration_value;
float min_allowed_value = 100;

// Method to read packing status
void checkPacking(){
  if(abs(slot1.getValue() - slot1_calibiration_value) > min_allowed_value) slot1_status = true;
  else slot1_status = false;
  if(abs(slot2.getValue() - slot2_calibiration_value) > min_allowed_value) slot2_status = true;
  else slot2_status = false;
  if(abs(slot3.getValue() - slot3_calibiration_value) > min_allowed_value) slot3_status = true;
  else slot3_status = false;
}

// // Method for posting slot status
void postData(){
  JSONVar json_post_object;
  json_post_object["slot1Status"] = slot1_status;
  json_post_object["slot2Status"] = slot2_status;
  json_post_object["slot3Status"] = slot3_status;
  String data_to_post = JSON.stringify(json_post_object);
  serialESP.println(data_to_post);
  Serial.println("POST: " + data_to_post);
}

// // MNethod to open the gate
void openGate(){
  Serial.println("Open the gate");
  for(int i=0; i<=90; i++){
    gate.write(i);
    delay(20);
  }
  delay(5e3);
  for(int i=90; i>=0; i--){
    gate.write(i);
    delay(20);
  }
}
