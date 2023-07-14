#include "Interface.h"
#include <EEPROM.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>
#define ESP_Rx A1
#define ESP_Tx A0

// Definition of pin connection
const uint8_t flowrate_pin=3, valve_pin=6;

// Decralation of objects
SoftwareSerial serialESP(ESP_Rx, ESP_Tx);

// Decralation of usefull variables
char charKey;
JSONVar json_object;
int units_address=0, time_out=30000;
String token, device_number = "1234567890";
float frequence, litters_per_min, litters_per_sec, units;

// Methode that calculate usage litters per sec
float usage() {
  int x = pulseIn(flowrate_pin, HIGH);
  int y = pulseIn(flowrate_pin, LOW);

  int pulse_duration = x - y;
  if(pulse_duration == 0) frequence = 0.00;
  else frequence = 1000000 / pulse_duration;
  litters_per_min = frequence / 7.5;
  litters_per_sec = litters_per_min / 60;

  if(litters_per_sec <= 0.0) litters_per_sec = 0.0;
  return litters_per_sec;
}

// Methode to handle getting Key from the Keypad
char get_key(){
  charKey = keypad.getKey();
  while(!charKey) charKey = keypad.getKey();
  return charKey;
}

// Method to handle insertion of token for payment
void payment(){
  token = "";
  lcdPrint("Enter token:", "");
  while(true){ // Wait for Customer to Enter Amount
    charKey = get_key();
    if(charKey >= '0' && charKey <= '9'){
      token = token + String(charKey);
      lcdPrint("Enter token:", token);
    }else if(charKey == '*'){
      token = token.substring(0, token.length() - 1);
      lcdPrint("Enter token:", token);
    }
    if(charKey == '#') break;
  }

  lcdPrint("Processing...", "");

  Serial.println("Prepair data to send");
  json_object["deviceNo"] = device_number;
  json_object["token"] = String(token);
  String json_string = JSON.stringify(json_object);
  Serial.println("Data: " + json_string);

  serialESP.println(json_string);
  Serial.println("Sent");
  
  unsigned long initial_time = millis();
  while(!serialESP.available()){
    if(millis() - initial_time > time_out) break;
  }
  if(serialESP.available()){
    
    String response = serialESP.readStringUntil('\r');
    response.trim();

    Serial.println("RESPONSE:'" + response + "'");
    lcdPrint("Server response", response); delay(2e3);

    if(response.toInt() == 0){
      lcdPrint("ERROR", "Invalid token");
      Serial.println("Invalid token");
    }else{
      lcdPrint("SUCCESS", "");
      units += response.toInt();
      EEPROM.put(units_address, units);
    }
  }else{
    lcdPrint("ERROR", "Time out");
    Serial.println("Time out");
  }
  delay(2e3);
}


void operation(){
  units -= usage()/10;
  if(units <= 0.0){
    units = 0.0;
    digitalWrite(valve_pin, LOW);
  }else digitalWrite(valve_pin, HIGH);

  EEPROM.put(units_address, units);
  lcdPrint("Electric meter", "Unit: " + String(units));

  charKey = keypad.getKey();
  if(charKey == '#') payment();
  delay(1e3);
}