/*
 * VicTech Electronics
 * Malole project 
 * FYP2022/23
 */
 
#include <SoftwareSerial.h>
SoftwareSerial serialESP(12, 11);

// Defition of pin connections
const uint8_t req_ind_pin=7, res_ind_pin=6, req_btn_pin=3, res_btn_pin=2, buzzer_pin=8;

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
  while(serialESP.available()){
    String serial_data = serialESP.readString();
    Serial.println(serial_data);
  }
}
