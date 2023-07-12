#include "Interface.h"

// Definitin of pin connections
const uint8_t fan_pin=6;

// Method for confirmation and cancelation
void confirmation(){
  confirm = true;
}
void cancelation(){
  cancel = true;
}

// Method for height settings
void setting(){
  if(confirm){
    delay(1e3); // Wait for deboucing of the button
    confirm = false;
    initial_height = height;
    while(!confirm){
      height = map(analogRead(pot_pin), 0, 1023, 0, 100);
      lcdPrint("Settings", "Height: " + String(height) + "%");

      if(cancel){
        lcdPrint("Settings", "CANCELED");
        delay(1e3); // Wait for deboucing of the button
        height = initial_height;
        cancel = false;
        return;
      }
    }delay(1e3); // Wait for deboucing of the button

    lcdPrint("Settings", "DONE");
    confirm = false;

    digitalWrite(fan_pin, HIGH);
    lcdPrint("Operation MODE", "...");
    delay(height * 1000);
  }
}