#include <EEPROM.h>
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>
#define ESP_Rx
#define ESP_Tx

// Decralation of objects
SoftwareSerial serialESP()

// Decralation of usefull variables
String token;
JSONVar json_object;

// Methode that calculate usage litters per sec
float usage() {
  x = pulseIn(flowrate, HIGH);
  y = pulseIn(flowrate, LOW);

  pulse_duration = x - y;
  if(pulse_duration == 0) frequence = 0.00;
  else frequence = 1000000 / pulse_duration;
  litters_per_min = frequence / 7.5;
  litters_per_sec = litters_per_min / 60;
  
  Serial.println("Pulse duration: " + String(x) + " - " + String(y) + " = " + String(pulse_duration));
  Serial.println("Frequence: " + String(frequence));
  Serial.println("L/s: " + String(litters_per_sec));
  return litters_per_sec;
}

// Method to handle insertion of token for payment
void payment(){
  lcd_print("Enter token:", "");
  while(true){ // Wait for Customer to Enter Amount
    charKey = get_key();
    if(charKey >= '0' && charKey <= '9'){
      token = token + String(charKey);
      lcd_print("Enter token:", token);
    }else if(charKey == '*'){
      token = token.substring(0, token.length() - 1);
      lcd_print("Enter token:", token);
    }
    if(charKey == '#') break;
  }


  json_object["device"] = device_number;
  json_object["token"] = token;
  String json_string = JSON.stringify(json_object);

  serialESP.println(json_string);
  
  unsigned long initial_time = millis();
  while(!serialESP.available()){
    if(millis() - initial_time > time_out){
      lcdPrint("ERROR", "Time out");
      Serial.println("Time out");
      break;
    }
  }
  String response = serialESP.readString();
  units += response.toInt();

  EEPROM.put(units_address, units);
}


void operation(){
  
}