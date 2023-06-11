#include <Servo.h>
#include <EEPROM.h>
#include "Interface.h"

Servo servo;

// Definition of pin connection
const uint8_t voltage_pin=A5, switch_pin=A4, servo_pin=6;

// Decralation of usefull variables
bool setting, confirm;
uint8_t timeAddress=0, sizeAddress=0;
int time = 0;
int size = 0;

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

  EEPROM.put(timeAddress, time);
  EEPROM.put(sizeAddress, size);
  digitalWrite(backlight, LOW);
  setting = false;
}


// Method to handle the whole operation
void operation(){
  if(setting) getSettings();
  lcdPrint("Automatic", "Fish feeder");
  unsigned long initial_time = millis();
  while(millis() - initial_time >= (time * 60000.0)); // Wait for time to pass

  for(byte i=0; i<90; i++){
    servo.write(i); 
    delay(20);
  }
  
  delay(map(size, 0, 100, 0, 10000));

  for(byte i=90; i>0; i--){
    servo.write(i); 
    delay(20);
  }
  
}