#include <Wire.h>
#include <EEPROM.h>
#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#define rows 4
#define cols 3

// Definition of pin connections in Microcontroller
int switch1=0, switch2=1, buzzer=5, sensor1=A3, sensor2=A1;

char keys[rows][cols]{
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte  row_pins[rows] = {7, 8, 9, 10}, col_pins[cols] = {11, 12, 13};

// Initialize the Keypad and LCD objects
Keypad keypad = Keypad(makeKeymap(keys), row_pins, col_pins, rows, cols);
LiquidCrystal_I2C lcd(0x27, 16, 2);


// Definition of useful variables
float pulse_duration, frequence, litters_per_min, litters_per_sec;
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


// Methode that calculate usage litters per sec
float usage() {
  x = pulseIn(flowrate, HIGH);
  y = pulseIn(flowrate, LOW);

  pulse_duration = x - y;
  if(pulse_duration == 0) frequence = 0.00;
  else frequence = 1000000 / pulse_duration;
  litters_per_min = frequence / 7.5;
  litters_per_sec = litters_per_min / 60;
  
  Serial.println("Pulse duration: " + String(x) + " - " + String(y) + " = " + String(pulse_duration));
  Serial.println("Frequence: " + String(frequence));
  Serial.println("L/s: " + String(litters_per_sec));
  return litters_per_sec;
}