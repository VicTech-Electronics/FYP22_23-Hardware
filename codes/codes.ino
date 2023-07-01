/*
  VicTech Electronics
  Likulike project
  FYP2022/23
  VTE51
*/
#include <stdlib.h>
#include "Operation.h"

// Decralation of usefull variables
bool operation_status, active_session;
unsigned long initial_time;
int session_time;

void setup() {
  pinMode(value_pin, OUTPUT);
  pinMode(format_btn, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();

  lcdPrint("Welcome", ""); delay(1e3);
  lcdPrint("Gas Vending", "System"); delay(1e3);
  lcdPrint("Initializing...", "");

  // Calculate Intital pressure
  initial_pressure = 0.0;
  for(byte i=0; i<100; i++){
    initial_pressure += getPressure();
    delay(100);
  }
  initial_pressure /= 100;
  EEPROM.get(unit_used_address, total_pressure_used);

  initializeSMS();
  attachInterrupt(digitalPinToInterrupt(format_btn), formatUsageISR, FALLING);
}

void loop() {
  String section = receivedSMS();
  if(section != ""){
    char* endPtr;
    session_time = strtol(section.c_str(), &endPtr, 10);
    if(*endPtr == "\0"){
      active_session = true;
      json_object["customer"] = device_id;
      json_object["title"] = "Starting session";
      json_object["details"] = "Cooking session started for about " + String(session_time) + " minute";
      json_string = JSON.stringify(json_object);
      postData(json_string, "notification");
    }
  }
  
  if(active_session){
    operation_status = true;
    if(millis() - initial_time >= session_time * 1000){
      active_session = false;
      operation_status = false;
      digitalWrite(value_pin, LOW);
    }
  }
  
  if(operation_status) operation();
}
