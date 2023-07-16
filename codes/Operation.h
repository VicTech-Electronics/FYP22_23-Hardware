#include "Interface.h"
#include "Control.h"

// Decralation of usefull variables
int service_cost;
String services[] = {"Urination", "Defecation", "Shower"};

// Method to provide change
void cashReturn(int amount){
  float i=0;
  if(amount >= 200){
    i = amount/200;
    while(i>=1){
      servoRotate(servo2);
      delay(1e3);
      i -= 1;
    }
    if(i!=0) servoRotate(servo1);
  }else if(amount >= 100){
    i = amount/100;
    while(i>=1){
      servoRotate(servo1);
      delay(1e3);
      i -= 1;
    }
    // if(i!=0) servoRotate(servo1);
  }
}

// Method to control the whole operation
void operation(){
  while(true){
    int coin = getCoin();
    if(coin == 0)
      lcdPrint("Please", "Insert coin");
    else
      break;
  }

  Serial.println("Coin received successfull");
  int i=0;
  
  while(!confirm){
    lcdPrint("Select service:", services[i]);
    if(digitalRead(btn2_pin) == LOW){
      delay(500);
      if(i>2)i=0;
      i++;
    }
  }

  // Assign the service cost
  if(i==0) service_cost=100;
  else if(i==1) service_cost=200;
  else if(i==2) service_cost=300;

  if(service_cost > coin_value){
    lcdPrint("Sorry:", "Low balance");
    cashReturn(coin_value);
  }else{
    lcdPrint("SUCCESS", "...");
    cashReturn(coin_value - service_cost);
    digitalWrite(lock_pin, HIGH); 
    delay(2e3);
    digitalWrite(lock_pin, LOW);
  }
  confirm = false;
}