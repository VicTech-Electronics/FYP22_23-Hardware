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

// Initialize the objects
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
// UltraSonicDistanceSensor ultrasonic(trig, echo);

// Decralation of other useful pins
const uint8_t buzzer_pin = 5, btn_pin = 3, trig_pin=6, echo_pin=7,
              indicator_pin = A1, backlight_pin = A0;

// Decralation of useful variables
boolean measure = false;
float distance=0.0;

// const int numSamples = 10;
// int samples[numSamples];
// int currentIndex = 0;


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



// Method to handle state Interrupt
void state(){
  measure = true;
  digitalWrite(buzzer_pin, HIGH);
  delayMicroseconds(15000);
  digitalWrite(buzzer_pin, LOW);
  delayMicroseconds(15000);
}

// Method to distance
float getDistance(){
  // Send a short pulse to the trigger pin
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  // Read the duration of the pulse from the echo pin
  long duration = pulseIn(echo_pin, HIGH);

  // Calculate the distance in centimeters
  // Speed of sound is approximately 343 meters per second
  // Divide by 2 to account for round trip travel of the sound wave
  return duration * 0.0343 / 2;
}



///////////////// Default methods /////////////////////
void setup() {
  pinMode(buzzer_pin, OUTPUT);
  pinMode(btn_pin, INPUT_PULLUP);
  pinMode(indicator_pin, OUTPUT);
  pinMode(backlight_pin, OUTPUT);
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  Serial.begin(9600);
  lcd.begin(16, 2);

  digitalWrite(backlight_pin, HIGH);
  attachInterrupt(digitalPinToInterrupt(btn_pin), state, FALLING);
}

void loop() {
  if(measure) {
    distance = 0.0;
    for(int i=0; i<100; i++){
      distance += getDistance();
      delay(10);
    }
    distance = distance / 100.0;
    digitalWrite(indicator_pin, HIGH);
    lcd_print("Distance Measure", "Dist: " + String(distance) + " cm.");
    delay(3e3);
    measure = false;
  }else
    digitalWrite(indicator_pin, LOW);
  

  lcd_print("Distance Measure", "Dist: " + String(distance) + " cm.");
  delay(500);
}
