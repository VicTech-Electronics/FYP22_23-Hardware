#include <SPI.h>
#include <Servo.h>
#include <HCSR04.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
#define TRIG_PIN1 A3
#define ECHO_PIN1 A2
#define TRIG_PIN2 A1
#define ECHO_PIN2 A0

Servo servo;
Servo servo1;
Servo servo2;
MFRC522 rfid(SS_PIN, RST_PIN);
UltraSonicDistanceSensor ultrasonic1(TRIG_PIN1, ECHO_PIN1);
UltraSonicDistanceSensor ultrasonic2(TRIG_PIN2, ECHO_PIN2);


// Definition of pins connections
const uint8_t btn1_pin=2, btn2_pin=3, buzzer_pin=4;

// Decralation of usefull variables
uint8_t detection_distance = 10;
bool doorStateISR, gateStateISR;

// Method to handle ISR function
void doorBtnISR(){
  doorStateISR = true;
}
void gateBtnISR(){
  gateStateISR = true;
}

// Method to read card number from rfid card reader
String getCardNumber(){
  if (rfid.PICC_IsNewCardPresent()) {
    if (rfid.PICC_ReadCardSerial()) {
      Serial.print("Card UID: ");
      String cardNumber = "";
      // Concatenate the UID bytes to form the card number
      for (byte i = 0; i < rfid.uid.size; i++) {
        cardNumber += rfid.uid.uidByte[i] < 0x10 ? "0" : "";
        cardNumber += String(rfid.uid.uidByte[i], HEX);
      }rfid.PICC_HaltA(); 
      Serial.println(cardNumber);
      return cardNumber;
    }
  }
  return "";
}

float getDistance(bool door){
  if(door) return ultrasonic1.measureDistanceCm();
  else return ultrasonic2.measureDistanceCm();
}

// Method to control servo motor to open gate
void open(bool door){
  if(door) servo = servo1;
  else servo = servo2;

  for(byte i=0; i<=90; i++){
    servo.write(i);
    delay(20);
  }

  while(true) if(getDistance(door) > detection_distance) break;
  
  for(byte i=90; i>0; i--){
    servo.write(i);
    delay(20);
  }
}


// Method to sound buzzer
void buzzerSound(){
  digitalWrite(buzzer_pin, HIGH);
  delay(1e3);
  digitalWrite(buzzer_pin, LOW);
}