#include <Keypad.h>
#include "Communication.h"

// Definition of pin connection
const uint8_t door1_pin=5, door2_pin=6, led1_pin=3, led2_pin=4;

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {A0, A1, A2, A3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {A4, A5, 2}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
Keypad keypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

// Decralation of usefull variables
char charKey;
String code;

// Methode to handle getting Key from the Keypad
char get_key(){
  charKey = keypad.getKey();
  while(!charKey) charKey = keypad.getKey();
  return charKey;
}

// Method to insert password
void insertPassword(){
  while(true){ // Wait for Customer to Enter Amount
    charKey = get_key();
    Serial.println("Key: " + String(charKey));
    if(charKey >= '0' && charKey <= '9'){
      code = code + String(charKey);
      String("Code: " + code);
    }else if(charKey == '*'){
      code = code.substring(0, code.length() - 1);
    }
    if(charKey == '#') {
      int number = random(0, 2);
      if(number == 0){
        digitalWrite(door1_pin, HIGH);
        digitalWrite(led1_pin, HIGH);
      }else if (required_service = 'S'){
        digitalWrite(door2_pin, HIGH);
        digitalWrite(led2_pin, HIGH);
      }

      delay(10e3);

      digitalWrite(door1_pin, LOW);
      digitalWrite(door2_pin, LOW);
      digitalWrite(led1_pin, LOW);
      digitalWrite(led2_pin, LOW);
      break;
    }
  }
}