/*
 * VicTech Electronics
 * Malole project 
 * FYP2022/23
 */
 
#include <SoftwareSerial.h>
SoftwareSerial serialESP(12, 11);

// Defition of pin connections
const uint8_t req_ind_pin, res_ind_pin, req_btn_pin, res_btn_pin, buzzer_pin;

/////////////////// Custom methods ///////////////////
// Method the handle request interrupt
void sendRequest(){
  digitalWrite(req_ind_pin, HIGH);
  digitalWrite(res_ind_pin, LOW);
  digitalWrite(buzzer_pin, HIGH);
  serialESP.println("request");
  Serial.println("Request sent");
  delayMicroseconds(15e3);
}

// Method the handle response interrupt
void sendResponse(){
  digitalWrite(req_ind_pin, LOW);
  digitalWrite(res_ind_pin, HIGH);
  digitalWrite(buzzer_pin, LOW);
  serialESP.println("response");
  Serial.println("Response sent");
  delayMicroseconds(15e3);
}
 
void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(req_ind_pin, OUTPUT);
  pinMode(res_ind_pin, OUTPUT);
  pinMode(req_btn_pin, INPUT_PULLUP);
  pinMode(res_btn_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialESP.begin(9600);
  
  attachInterrupt(digitalPinToInterrupt(req_btn_pin), sendRequest, FALLING);
  attachInterrupt(digitalPinToInterrupt(res_btn_pin), sendResponse, FALLING);

  Serial.println("System is started");
}

void loop() {
}
