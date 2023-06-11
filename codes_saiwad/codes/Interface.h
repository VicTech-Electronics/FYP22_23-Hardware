#include <LiquidCrystal.h>

// Definition of pin connections
const uint8_t buzzer_pin=6, btn_pin=2, acceptor_pin=5, backlight_pin=7;

// Initialize the Objects
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Decralation of usefull variables
int pulse_counter, coin_value, charging_time;
const unsigned long pulse_counting_time = 5000;

////////////////* Custom methods (Functions) */////////////////////////
// Methode to Cut String 
String cutString(String str, int col) {
  return str.substring(0, col);
}
// Function to simplify the printing on LCD
void lcdPrint(String str0, String str1) {
  lcd.clear();  const int columns = 16;
  if (str0.length() > columns) str0 = cutString(str0, columns);
  if (str1.length() > columns) str1 = cutString(str1, columns);

  int pre_space0 = int((columns - str0.length()) / 2),
      pre_space1 = int((columns - str1.length()) / 2);

  lcd.setCursor(pre_space0, 0); lcd.print(str0);
  lcd.setCursor(pre_space1, 1); lcd.print(str1);
  delay(1e3);
}

// Method to check the coin inserted
void getCoinValue(){
  pulse_counter = 0;
  unsigned long initial_time = millis();
  while(millis() - initial_time > pulse_counting_time){
    if(digitalRead(acceptor_pin) == LOW){
      pulse_counter++;
      while(digitalRead(acceptor_pin) == LOW){}
    }
  }

  switch(pulse_counter){
    case 2:
      coin_value = 50;
      charging_time = 5000;
      break;
    case 3:
      coin_value = 100;
      charging_time = 10000;
      break;
    case 4:
      coin_value = 200;
      charging_time = 20000;
      break;
    case 5:
      coin_value = 500;
      charging_time = 50000;
      break;
    default:
      coin_value = 0;
      charging_time = 0;
      break;
  }
}