#include <Wire.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal.h>
#define rows 4
#define cols 3

// Definition of pin connections in Microcontroller
const int8_t buzzer_pin=6;


char keys[rows][cols]{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte  row_pins[rows] = {7, 8, 9, 10}, col_pins[cols] = {11, 12, 13};

// Initialize the Keypad and LCD objects
Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, rows, cols);
LiquidCrystal lcd(A5, A4, A3, A2, A1, A0);

// Methode to simplify the printing in LCD
void lcd_print(String str0, String str1) {
  lcd.clear();  const int columns = 16;
  if (str0.length() > columns) str0 = cut_string(str0, columns);
  if (str1.length() > columns) str1 = cut_string(str1, columns);

  int pre_space0 = int((columns - str0.length()) / 2),
      pre_space1 = int((columns - str1.length()) / 2);

  lcd.setCursor(pre_space0, 0); lcd.print(str0);
  lcd.setCursor(pre_space1, 1); lcd.print(str1);
}
String cut_string(String str, int col){
  return str.substring(0, col);
}