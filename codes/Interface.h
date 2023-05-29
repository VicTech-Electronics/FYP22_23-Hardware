#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

// Definition of usefull pins 
const uint8_t btn_pin=3, buzzer_pin=6, backlight_pin=7,
              main_ind_pin=A3, inv_ind_pin=A4, sense_pin=4;

// Decralation of usefull variable and constants
bool backlight_state = false;

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
  delay(100);
}