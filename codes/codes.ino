/*
 * VicTech Electronics 
 * This is program codes for distance project VTE22
 * FYP2022/23 (Diploma project)
 */
#include <HCSR04.h>
#include <LiquidCrystal.h>
#define rs 8
#define en 9
#define d4 10
#define d5 11
#define d6 12
#define d7 13
#define trig 6
#define echo 7

// Initialize the objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
UltraSonicDistanceSensor ultrasonic(trig, echo);

// Decralation of other useful pins
const uint8_t buzzer_pin = 5, btn_pin = 3,
              indicator_pin = A1, backlight_pin = A0;


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
  delay(100);
}

// Methode to Cut String 
String cut_string(String str, int col) {
  return str.substring(0, col);
}

// Decralation of useful variables
boolean measure = false;
float distance;

// Method to handle state Interrupt
void state(){
  measure = !measure;
  digitalWrite(buzzer_pin, HIGH);
  delayMicroseconds(15e3);
  digitalWrite(buzzer_pin, LOW);
}



///////////////// Default methods /////////////////////
void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(indicator_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  attachInterrupt(digitalPinToInterrupt(btn_pin), state, FALLING);
}

void loop() {
  if(measure) {
    distance = ultrasonic.measureDistanceCm();
    digitalWrite(indicator_pin, HIGH);
    digitalWrite(backlight_pin, HIGH);
  }else{
    digitalWrite(indicator_pin, LOW);
    digitalWrite(backlight_pin, LOW);
  }

  lcd_print("Distance Measure", "Dist: " + String(distance) + " cm.");
  delay(500);
}
