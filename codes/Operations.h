#include "Interface.h"
#include "Functions.h"

// Decralation of usefull variables
String serial_data, card_number;

// Method to control the whole operation
void operation(){
  card_number = getCardNumber();

  if(card_number != ""){
    Serial.println(card_number);
    buzzerSound();
    while(!Serial.available()); // Wait for return form the AI
    serial_data = Serial.readString();

    if(serial_data == "exist") open(true);
  }

  if(getDistance(false) < detection_distance){
    Serial.println("capture");
    buzzerSound();
    while(!Serial.available()); // Wait for return form the AI
    serial_data = Serial.readString();

    if(serial_data == "exist") open(false);
  }
}