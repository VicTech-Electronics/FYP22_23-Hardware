#include <LiquidCrystal.h>

// Decralation of pin configurations
const int backlight_pin = 8;

// Decralation of usefull variable

// Initialize the Objects
LiquidCrystal lcd(13, 12, 11, 10, 9, 6);


////////////////* Custom methods (Functions) */////////////////////////
// Function to simplify the printing on LCD
void lcd_print(String str0, String str1) {
  lcd.clear();  const int columns = 16;
  if (str0.length() > columns) str0 = cut_string(str0, columns);
  if (str1.length() > columns) str1 = cut_string(str1, columns);

  int pre_space0 = int((columns - str0.length()) / 2),
      pre_space1 = int((columns - str1.length()) / 2);

  lcd.setCursor(pre_space0, 0); lcd.print(str0);
  lcd.setCursor(pre_space1, 1); lcd.print(str1);
  delay(1e3);
}

// Methode to Cut String 
String cut_string(String str, int col) {
  return str.substring(0, col);
}


/////////////// Defaul methods ///////////////////
void setup() {
  pinMode(backlight_pin, OUTPUT);
  
  Serial.begin(9600);
  lcd.begin(16, 2);
  digitalWrite(backlight_pin, HIGH);

  lcd_print("Welcome", ""); delay(1e3);
  lcd_print("UDSM Student", "2019-04-11366"); delay(1e3);
  lcd_print("Energy Meter", "-------------"); delay(1e3);


  lcd_print("Energy Meter", "0.00 KWh"); delay(5e3);
  digitalWrite(backlight_pin, LOW);
}

void loop() {
  // put your main code here, to run repeatedly:

}
