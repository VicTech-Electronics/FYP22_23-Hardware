#include "Sense.h"
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

////////////////////////////////////
String vehicle_number = "T123-ABC";
////////////////////////////////////

// Objects
SoftwareSerial serialESP(12, 9);
JSONVar jsonObject, jsonString;

// Definition of useful pins
const uint8_t confirm_BTN=2, cancel_BTN=3, buzzer_pin=8, serial_interrupt_pin=5;


float latitudes[5] = {-6.814432, -6.814469, -6.814410, -6.814517, -6.814426};
float longitudes[5] = {39.280177, 39.280059, 39.280188, 39.280107, 39.280053};

// Decralation of useful variables
String serial_data, json_string;
float latitude, longitude;
bool confirm=false, cancel=false;

//////////// Custome functions //////////////
// Function to handle ISR
void confirmISR(){
  Serial.println("Confirm button is pressed");
  confirm = true;
}
void cancelISR(){
  Serial.println("Cancel button is pressed");
  cancel = true;
}

// Function to get location data
void getLocation(){
  int index = random(0, 5);
  latitude = latitudes[index];
  longitude = longitudes[index];
}

// Functions to handle accident confirmation and cancelation Interrupts
void confirmation(){
  if(confirm){
    Serial.println("Confirmation is proccessed");

    getLocation();
    // Send data to the site
    Serial.print("# {\"vehicle\": \"");
    Serial.print(vehicle_number);
    Serial.print("\"");
    Serial.print(",\"latitude\": ");
    Serial.print(latitude, 5);
    Serial.print(",\"longitude\": ");
    Serial.print(longitude, 5);
    Serial.println("}");

    // Send data to the site
    serialESP.print("# {\"vehicle\": \"");
    serialESP.print(vehicle_number);
    serialESP.print("\"");
    serialESP.print(",\"latitude\": ");
    serialESP.print(latitude, 5);
    serialESP.print(",\"longitude\": ");
    serialESP.print(longitude, 5);
    serialESP.println("}");

    serial_data = "";
    while(serialESP.available()){
      serial_data += serialESP.readString();
    }
    serial_data = serialESP.readString();
    serial_data.trim();
    Serial.println("serialESP data: " + serial_data);
    if(serial_data.indexOf("SUCCESS") != -1) digitalWrite(buzzer_pin, HIGH);

    confirm = false;
  }
}

void cancelation(){ 
  if(cancel){
    Serial.println("Cancellation is processed");
    serialESP.println("/api/cancel/" + vehicle_number);
    delay(2e3);
    cancel = false; 
  }
}


// Method to correct accident data and post
void postAccientData(){
    // Check gyroscopic value greater than others
    float gyrospcopic_data;
    if (roll > pitch) gyrospcopic_data = roll;
    else gyrospcopic_data = pitch;

    getLocation();
    // Send data to the site
    Serial.print("@ {\"vehicle\": \"");
    Serial.print(vehicle_number);
    Serial.print("\"");
    Serial.print(",\"flame\": ");
    Serial.print(digitalRead(flame_pin));
    Serial.print(",\"smoke\": ");
    Serial.print(analogSensor(smoke_pin));
    Serial.print(",\"vib\": ");
    Serial.print(analogSensor(vibration_pin));
    Serial.print(",\"gyro\": ");
    Serial.print(gyrospcopic_data);
    Serial.print(",\"lat\": ");
    Serial.print(latitude, 5);
    Serial.print(",\"long\": ");
    Serial.print(longitude, 5);
    Serial.println("}");

    // Send data to the site
    serialESP.print("@ {\"vehicle\": \"");
    serialESP.print(vehicle_number);
    serialESP.print("\"");
    serialESP.print(",\"flame\": ");
    serialESP.print(digitalRead(flame_pin));
    serialESP.print(",\"smoke\": ");
    serialESP.print(analogSensor(smoke_pin));
    serialESP.print(",\"vib\": ");
    serialESP.print(analogSensor(vibration_pin));
    serialESP.print(",\"gyro\": ");
    serialESP.print(gyrospcopic_data);
    serialESP.print(",\"lat\": ");
    serialESP.print(latitude, 5);
    serialESP.print(",\"long\": ");
    serialESP.print(longitude, 5);
    serialESP.println("}");

    while(!serialESP.available())
      Serial.println("Wait for ESP response");

    serial_data = "";
    while(serialESP.available()){
      serial_data += serialESP.readString();
    }
    serial_data.trim();
    Serial.println("serialESP data: " + serial_data);
    if(serial_data.indexOf("Detected") != -1) digitalWrite(buzzer_pin, HIGH);
}