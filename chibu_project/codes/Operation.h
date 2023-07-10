#include <stdint.h>
#include "Interface.h"
#include "Communication.h"
#include <Arduino_JSON.h>

// Objects
JSONVar jsonObject;

// Decralation of usefull variables
uint8_t password;
String card_number;
String services[] = {"Urination", "Defecation", "Shower", "Cancel"};
int serviceCost[] = {200, 300, 500};
bool confirm, cancel;


// Methode to handle confirm and cancel interrupt
void confirmation(){
  confirm = true;
}
void cancelation(){
  cancel = true;
}

// Method to handle the whole system operation
void operation(){
  lcdPrint("Please", "Scan your card");
  card_number = "";
  while(card_number == ""){
    card_number = getCardNumber();
  } // Wait for card to be scanned
    

  byte counter = 0;
  while(!confirm){
    lcdPrint("Select service", services[counter]);
    if(!cancel){ 
      delay(1e3); // Wait for debouce of the button
      counter++; 
      cancel=false;
      if(counter > 3) counter = 0;
    }
  } confirm = false;

  if(counter == 3) return; // Cancel proccess if no service requied
  
  jsonObject["customer"] = card_number;
  jsonObject["details"] = "Requested for " + services[counter] + " service";
  jsonObject["amount"] = serviceCost[counter];
  String serial_data = JSON.stringify(jsonObject);

  String response = espRequest(serial_data);

  if(response.indexOf("SUCCESS") != -1){
    // Generate password
    password = random(0, 9999);
    char formated_password[5];
    sprintf(formated_password, "%04d", password);
    password = int(formated_password);

    lcdPrint("Press", "Confirm button");
    while(!confirm); confirm = false; // Wait for confirmation

    if(counter == 0) nrfSend(password, 'U');
    if(counter == 1) nrfSend(password, 'D');
    if(counter == 2) nrfSend(password, 'S');

    lcdPrint("Password", String(password));
    delay(5e3);
  }else if(response.indexOf("Cardnumber not exist") != -1)
    lcdPrint("Error", "Cardnumber not exist");
  else
    lcdPrint("Sorry", "Operation failed");
}