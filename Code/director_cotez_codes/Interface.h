#include <LiquidCrystal.h>

// Initialize the Objects
LiquidCrystal lcd(13, 12, 11, 10, 9, 6);

// Decralation of pin configurations
const int backlight_pin = 8;

// Decralation of usefull variable


// Function to simplify the printing on LCD
String cutString(String str, int col) {
  return str.substring(0, col);
}

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