/*
 * VicTech Electronics
 * Malole project 
 * FYP2022/23
 */
 
#include <SoftwareSerial.h>
SoftwareSerial serialESP(12, 11);

// Defition of pin connections
const uint8_t req_ind_pin=7, res_ind_pin=6, req_btn_pin=3, res_btn_pin=2, buzzer_pin=8;

// Decralation of usefull variable
bool response, request;

/////////////////// Custom methods ///////////////////
// Method the handle request interrupt
void responseISR(){
  response = true;
}
void requestISR(){
  request = true;
}

void sendRequest(){
  digitalWrite(req_ind_pin, HIGH);
  digitalWrite(res_ind_pin, LOW);
  digitalWrite(buzzer_pin, HIGH);
  serialESP.println("request");
  Serial.println("Request sent");
  delay(3e3);
  request = false;
}

void sendResponse(){
  digitalWrite(req_ind_pin, LOW);
  digitalWrite(res_ind_pin, HIGH);
  digitalWrite(buzzer_pin, LOW);
  serialESP.println("response");
  Serial.println("Response sent");
  delay(3e3);
  response = false;
}
 
void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(req_ind_pin, OUTPUT);
  pinMode(res_ind_pin, OUTPUT);
  pinMode(req_btn_pin, INPUT_PULLUP);
  pinMode(res_btn_pin, INPUT_PULLUP);

  Serial.begin(9600);
  serialESP.begin(9600);
  digitalWrite(res_ind_pin, HIGH);
  
  attachInterrupt(digitalPinToInterrupt(req_btn_pin), requestISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(res_btn_pin), responseISR, FALLING);

  Serial.println("System is started");
}

void loop() {
  if(response) sendResponse();
  if(request) sendRequest();

  while(serialESP.available()){
    String serial_data = serialESP.readString();
    Serial.println(serial_data);
  }
}
