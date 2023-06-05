#include <Servo.h>
#include <EEPROM.h>
#include "Interface.h"

Servo servo;

// Definition of pin connection
const uint8_t voltage_pin=A5, switch_pin=A4, servo_pin=6;

// Decralation of usefull variables
bool setting, confirm;
uint8_t time, size, timeAddress=0, sizeAddress=0;

// Method to handle Interrupts
void settingsInterrupt(){
  setting = true;
}
void confirmationInterrupt(){
  confirm = true;
}

// Method to control automatic change over
void changeOver(){
  if(digitalRead(voltage_pin) == HIGH) digitalWrite(switch_pin, HIGH);
  else digitalWrite(switch_pin, LOW);
}

// Method to control settings
void getSettings(){
  confirm = false;
  while(!confirm){
    time = map(analogRead(pot_pin), 0, 1023, 0, 5);
    lcdPrint("SETTING", "Time: " + String(time) + " min");
  }
  
  confirm = false;
  while(!confirm){
    size = map(analogRead(pot_pin), 0, 1023, 0, 100);
    lcdPrint("SETTING", "Size: " + String(size) + " min");
  }

  EEPROM.put(timeAddress, time);
  EEPROM.put(sizeAddress, size);

  setting = false;
}


// Method to handle the whole operation
void operation(){
  if(setting) getSettings();
  
  unsigned long initial_time = millis();
  while(millis() - initial_time > (time)); // Wait for time to pass

  servo.write(90);
  delay(map(size, 0, 100, 0, 5000));
  servo.write(0);
}