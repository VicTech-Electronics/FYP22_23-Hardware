#include "DataFile.h"

// Decrlation of useful variable
unsigned long initial_time;

void setup(){
  pinMode(flame_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);

  Serial.begin(9600);
  serialESP.begin(9600);

  Wire.begin(); // Initialize the I2C library
  Wire.beginTransmission(MPU_addr); // Start communication with MPU6050
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // Wake up the MPU6050
  Wire.endTransmission(true);
  delay(3e3);

  // Initialize SD card
  if (!SD.begin(chip_selector_pin)) {
    Serial.println("SD card initialization failed!");
    while (true);
  } Serial.println("SD card initialization SUCCESS");

  initial_time = millis();
}

void loop() {
  if(millis() - initial_time > 5000){
    storeDataInMemory();
    initial_time = millis();
  }
  
  if(roll > 45 || pitch > 45 ||
    vibration_value >= 50 ||
    smoke_value >= 50 ||
    digitalRead(flame_pin) == HIGH
  ){
    digitalWrite(buzzer_pin, HIGH);
    getLocation();
    Serial.println("Send data");

    // Print data to the serial monitor
    Serial.print("{\"vehicle_number\": \"");
    Serial.print(vehicle_number);
    Serial.print("\"");
    Serial.print(",\"latitude\": ");
    Serial.print(latitude, 5);
    Serial.print(",\"longitude\": ");
    Serial.print(longitude, 5);
    Serial.println(",\"description\": \"Information stored in the BlackBox from the car\"}");

    // Send data to the site
    serialESP.print("{\"vehicle_number\": \"");
    serialESP.print(vehicle_number);
    serialESP.print("\"");
    serialESP.print(",\"latitude\": ");
    serialESP.print(latitude, 5);
    serialESP.print(",\"longitude\": ");
    serialESP.print(longitude, 5);
    serialESP.println(",\"description\": \"Information stored in the BlackBox from the car\"}");
    
    
    while(!serialESP.available());
    while(serialESP.available()){
      data = serialESP.readString();
      Serial.println("Data from serialESP: " + data);
    }

    digitalWrite(buzzer_pin, LOW);
  }
}