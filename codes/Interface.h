
#include <LiquidCrystal.h>
LiquidCrystal lcd(8, 9, 10, 11, 12, 13);

// Methode to cut string
String cutString(String str, int col){
  return str.substring(0, col);
}

// Method to simplify LCD printing
void lcdPrint(String str0, String str1, String str2, String str3){
  lcd.clear();  const int columns = 20;
  if (str0.length() > columns) str0 = cutString(str0, columns);
  if (str1.length() > columns) str1 = cutString(str1, columns);
  if (str2.length() > columns) str2 = cutString(str2, columns);
  if (str3.length() > columns) str3 = cutString(str3, columns);

  int pre_space0 = int((columns - str0.length()) / 2),
      pre_space1 = int((columns - str1.length()) / 2),
      pre_space2 = int((columns - str2.length()) / 2),
      pre_space3 = int((columns - str3.length()) / 2);

  lcd.setCursor(pre_space0, 0); lcd.print(str0);
  lcd.setCursor(pre_space1, 1); lcd.print(str1);
  lcd.setCursor(pre_space2, 2); lcd.print(str2);
  lcd.setCursor(pre_space3, 3); lcd.print(str3);
  
  delay(1e3);
}