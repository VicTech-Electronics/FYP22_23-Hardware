#include "Communication.h"
#include "Interface.h"

// Definition of pin connection
const uint8_t port1_pin=A3, port2_pin=A4, port3_pin=A5;

// Declaration of usefull variables
uint8_t available_port = 1;
bool is_port1, is_port2, is_port3;
int number_of_phone_charged = 0, amount_received = 0;
unsigned long initial_time1=0, initial_time2=0, initial_time3=0;
unsigned long charging_time1=0, charging_time2=0, charging_time3=0;
int pulse_counter, coin_value, charging_time;
unsigned long count_rate;

// Method to handle the interrupt pulse counter
void coutingPulseISR(){
  pulse_counter++;
  count_rate=0;
}
 
// Method to handle port to switch
void switchPort(int port, boolean state){
  if(port == 1) digitalWrite(port1_pin, state);
  else if(port == 2) digitalWrite(port2_pin, state);
  else if(port == 3) digitalWrite(port3_pin, state);
}

int getCoinValue(){
  coin_value = 0;
  switch(pulse_counter){
    case 2:
      coin_value = 50;
      break;
    case 3:
      coin_value = 100;
      break;
    case 4:
      coin_value = 200;
      break;
    case 5:
      coin_value = 500;
      break;
    default:
      coin_value = 0;
      break;
  }
  return coin_value;
}

// Method to handle product choice
void service(){
  if(getCoinValue() > 0){
    lcdPrint("Available", "Port " + String(available_port) + "is free");
    // Calculate charging time
    if(coin_value == 50) charging_time = 10e3;
    else if(coin_value == 100) charging_time = 30e3;
    else if(coin_value == 200) charging_time = 60e3;
    else if(coin_value == 500) charging_time = 150e3;
    else charging_time = 0;

    if(available_port == 1){
      initial_time1 = millis();
      charging_time1 = charging_time;
    }else if(available_port == 2){
      initial_time2 = millis();
      charging_time2 = charging_time;
    }else if(available_port == 3){
      initial_time3 = millis();
      charging_time3 = charging_time;
    }

    if(available_port > 0){
      switchPort(available_port, LOW);
      amount_received += coin_value;
      number_of_phone_charged++;

      lcdPrint("Enjoy service", "Port: " + String(available_port));
      available_port ++;
      if(available_port > 3) available_port = 0;
    }
  }

  pulse_counter = 0;
}


// Method to calculate charging time 
void calculateChargingTime(){
  // Calculate the charging time and switch  OFF if its Over
  if(millis() - initial_time1 >= charging_time1 && initial_time1 != 0){
    switchPort(1, HIGH);
    available_port--;
    initial_time1 = 0;
  }
  if(millis() - initial_time2 >= charging_time2 && initial_time2 != 0){
    switchPort(2, HIGH);
    available_port--;
    initial_time2 = 0;
  }
  if(millis() - initial_time3 >= charging_time3 && initial_time3 != 0){
    switchPort(3, HIGH);
    available_port--;
    initial_time3 = 0;
  }

  if(available_port < 0) available_port=0;
}