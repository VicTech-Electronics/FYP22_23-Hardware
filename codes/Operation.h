#include <Servo.h>
#include "Interface.h"

// Definition of pin connection
const int8_t servo_pin=3;

// Decralation of useful variables
char charKey;
String password, correct_password = "2023";

// Object
Servo servo;

// Methode to handle getting Key from the Keypad
char getCharKey(){
  charKey = keypad.getKey();
  while(!charKey) charKey = keypad.getKey();
  return charKey;
}


// Method to handle the whole operation
void operation(){
  password = "";
  lcdPrint("Enter Password", "_");

  while(true){ // Wait for password
    charKey = getCharKey();
    if(charKey >= '0' && charKey <= '9'){
      password = password + String(charKey);
      lcdPrint("Password", password + "_");
    }else if(charKey == '*'){
      password = password.substring(0, password.length() - 1);
      lcdPrint("Password", password + "_");
    }else if(charKey == '#') break;
  }

  if(password = correct_password){
    lcdPrint("SUCCESS", ""); delay(2e3);
    lcdPrint("Opening...", "");
    servo.write(90);
    delay(3e3);

    for(byte i=5; i>0; i--){
      lcdPrint("Remaing time:", String(i) + " sec.");
      delay(1e3);
    }

    lcdPrint("Closing...", "");
    servo.write(0);
    delay(3e3);
  }else{
    lcdPrint("Incorect Password", "");
    digitalWrite(buzzer_pin, HIGH);
    delay(3e3);
    digitalWrite(buzzer_pin, LOW);
  }
}