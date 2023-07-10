#include "Interface.h"
#include "Communication.h"

// Definition of pin connection
const uint8_t door1_pin=5, door2_pin=6, led1_pin=3, led2_pin=4;

// Method to handle the whole operation of the system 
void operation(){
  if(receiveData()){
    insertPassword();

    if(code = password){
      if(required_service == 'U' || required_service == 'D'){
        digitalWrite(door1_pin, HIGH);
        digitalWrite(led1_pin, HIGH);
      }else if (required_service = 'S') {
        digitalWrite(door2_pin, HIGH);
        digitalWrite(led2_pin, HIGH);
      }
    }
    delay(10e3);

    digitalWrite(door1_pin, LOW);
    digitalWrite(door2_pin, LOW);
    digitalWrite(led1_pin, LOW);
    digitalWrite(led2_pin, LOW);
  }
}