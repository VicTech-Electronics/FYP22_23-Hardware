#include <Servo.h>
#include <EEPROM.h>
#include "Interface.h"

Servo servo;

// Definition of pin connection
const uint8_t voltage_pin=A5, switch_pin=A4, servo_pin=6;

// Decralation of usefull variables
bool setting, confirm;
uint8_t timeAddress=0, sizeAddress=5;
int time = 0;
int size = 0;
int delay_time;

// Method to handle Interrupts
void settingsInterrupt(){
  setting = true;
  Serial.println("Setting button is pressed");
}
void confirmationInterrupt(){
  confirm = true;
  Serial.println("Confirm button is pressed");
}

// Method to control automatic change over
void changeOver(){
  if(digitalRead(voltage_pin) == HIGH) digitalWrite(switch_pin, HIGH);
  else digitalWrite(switch_pin, LOW);
}

// Method to control settings
void getSettings(){
  digitalWrite(backlight, HIGH);
  confirm = false;
  while(!confirm){
    time = map(analogRead(pot_pin), 0, 1023, 0, 10);
    lcdPrint("SETTING", "Time: " + String(time) + " min");
    delay(100);
  }

  delay(2e3);
  
  confirm = false;
  while(!confirm){
    size = map(analogRead(pot_pin), 0, 1023, 0, 100);
    lcdPrint("SETTING", "Size: " + String(size) + "%");
    delay(100);
  }

  delay_time = map(size, 0, 100, 0, 10000);
  EEPROM.put(timeAddress, time);
  EEPROM.put(sizeAddress, size);
  digitalWrite(backlight, LOW);
  setting = false;

  Serial.println("Time: " + String(time));
  Serial.println("Size: " + String(size));
  Serial.println("Delay time: " + String(delay_time));

  int time_data, size_data;
  EEPROM.get(timeAddress, time_data);
  EEPROM.get(sizeAddress, size_data);

  Serial.println("Reading from EEPROM");
  Serial.println("Time EEPROM: " + String(time_data));
  Serial.println("Size EEPROM: " + String(size_data));
}


// Method to handle the whole operation
void operation(){
  if(setting) getSettings();
  lcdPrint("Automatic", "Fish feeder");
  unsigned long initial_time = millis();
  float waiting_time = time * 60000.0;
  while(millis() - initial_time < waiting_time){
    Serial.println("Waiting for given time");
    if(setting) getSettings();
    delay(100);
  }

  for(byte i=0; i<90; i++){
    servo.write(i); 
    delay(20);
  }
  
  delay(delay_time);

  for(byte i=90; i>0; i--){
    servo.write(i); 
    delay(20);
  }
  
}