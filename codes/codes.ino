/*
  VicTech Electronics
  AbelGeorge Project
  FYP2022/23
  VTE20
*/

#include "Interface.h"

// Decralation of usefull variables
bool old_state, change = false;

// Method to handle backlight operation
void backlightControl(){
  digitalWrite(backlight_pin, !backlight_state);
  delayMicroseconds(16e3);
}


// Default methods
void setup() {
  pinMode(sense_pin, INPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(inv_ind_pin, OUTPUT);
  pinMode(main_ind_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(backlight_pin, OUTPUT);

  lcd.begin(16, 2);
  
  old_state = digitalRead(sense_pin);
  attachInterrupt(digitalPinToInterrupt(btn_pin), backlightControl, FALLING);
}

void loop() {
  if(digitalRead(sense_pin) == HIGH){
    digitalWrite(inv_ind_pin, LOW);
    digitalWrite(main_ind_pin, HIGH);
    lcdPrint("Auto Changeover:", "MAIN SUPPLY");   
  }else{
    digitalWrite(inv_ind_pin, HIGH);
    digitalWrite(main_ind_pin, LOW);
    lcdPrint("Auto Changeover:", "INVERTER");
  } 

  if(old_state != digitalRead(sense_pin)){
    old_state = digitalRead(sense_pin);
    change = true;
  }

  if(change){
    digitalWrite(buzzer_pin, HIGH);
    delay(2e3);
    digitalWrite(buzzer_pin, LOW);
    change = false;
  }
}
