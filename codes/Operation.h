#include <Arduino_JSON.h>
#include "Interface.h"
#include "Communication.h"

// Definition of usefull pin connection
const uint8_t step1_pin=A1, step2_pin=A3, dir1_pin=A0, dir2_pin=A2;

JSONVar json_object;

// Decralation of usefull variables
uint8_t number_of_pads, steps_per_value = 230, pad_type;
int amount, amout_per_pad = 500;
bool confirm, cancel;
String response, pad_name;

// Method to handle confirmation and cancelation Interrupts
void confirmation(){
  Serial.println("Confirm buttons in pressed");
  confirm = true;
}
void cancelation(){
  Serial.println("Cancel buttons in pressed");
  cancel = true;
}

// Methode to rotate motors
void padOut(byte type, byte value){
  int pin;
  if(type == 1) pin = step1_pin;
  else if(type == 2) pin = step2_pin;

  uint8_t steps = value * steps_per_value;
  for(byte i=0; i<steps; i++){
    digitalWrite(pin, HIGH);
    delayMicroseconds(5e3);
    digitalWrite(pin, LOW);
    delayMicroseconds(5e3);

    if(i % steps_per_value == 0) delay(2e3); // Wait for Pad to drop
  }
}

// Method to send request to the server
String sendRequest(){
  json_object["card_number"] = card_number;
  json_object["amount"] = amount;
  json_object["details"] = "Purchase " + String(number_of_pads) + " pads";
  String json_string = JSON.stringify(json_object);

  serialESP.println(json_string);

  // Wait for the response
  unsigned long initial_time = millis();
  while(millis() - initial_time >= 5000){
    if(serialESP.available())
      return serialESP.readString();
  }
  return "time_out";
}


// Method to handle service operation
void service(){
  // Scann card
  lcdPrint("Please", "Scann your card");
  number_of_pads = 1; pad_type = 1;
  card_number = ""; 
  while(card_number == ""){
    card_number = getCardNumber();
  }
  
  // Chose pad type
  confirm = false;
  while(!confirm){
    if(pad_type==1) pad_name = "Softcare";
    else pad_name = "HC";
    lcdPrint("Pad type", "Choice: " + String(pad_name) + " Pads");
    if(cancel){
      if(pad_type == 1) pad_type = 2;
      else pad_type = 1;
      cancel = false;
      delay(1e3);
    }
  }confirm = false;

  // Select number of pads required
  confirm = false;
  while(!confirm){
    lcdPrint("Number of pads", "Choice: " + String(number_of_pads) + " Pads");
    if(cancel){
      number_of_pads++;
      cancel = false;
      delay(1e3);
    }
  }confirm = false;
  
  // Confirm payment
  amount = number_of_pads * amout_per_pad;
  lcdPrint("Confirm payment", String(number_of_pads) + "Pads, " + String(amount) + "Tsh.");
  bool wait = true;
  while(wait){
    Serial.println("Waiting");
    if(confirm){
      lcdPrint("Please wait", "...");
      response = sendRequest();

      if(response.indexOf("SUCCESS") != -1){
        padOut(pad_type, number_of_pads);
        lcdPrint("SUCCESS", "");
      }else if(response.indexOf("Insufficient balance") != -1)
        lcdPrint("Sorry", "Out of balance");
      else if(response.indexOf("FAIL") != -1)
        lcdPrint("Sorry", "Operation failed");
      else lcdPrint("NETWORK ERROR", "Timeout");

      wait = false;
    }else if(cancel){
      lcdPrint("CANCELLED", "");
      wait = false;
    }
  }

  confirm = false;
  cancel = false;
  delay(3e3);
}