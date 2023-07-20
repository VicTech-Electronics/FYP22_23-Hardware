#include "Interface.h"

// Method to handle the whole operation of the system 
void operation(){
  if(receiveData()){
    digitalWrite(led1_pin, HIGH);
    digitalWrite(led2_pin, HIGH);
    delay(2e3);
    digitalWrite(led1_pin, LOW);
    digitalWrite(led2_pin, LOW);

    Serial.println("Data received form circuit 1");
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