#include "Sense.h"
#include <Arduino_JSON.h>
#include <SoftwareSerial.h>

#define ACCIDENT "detected"

////////////////////////////////////
String vehicle_number = "T123-ABC";
////////////////////////////////////

// Objects
SoftwareSerial serial(6, 7);
SoftwareSerial serialESP(12, 9);
JSONVar jsonObject, jsonString;

// Definition of useful pins
const uint8_t confirm_BTN=2, cancel_BTN=3, buzzer_pin=8, serial_interrupt_pin=5;

// Decralation of useful variables
String serial_data, json_string;
float latitude, longitude;

//////////// Custome functions //////////////

// Method to initialize serial com
bool serialInit(){
  serial.listen();
  digitalWrite(serial_interrupt_pin, HIGH);
  while(!serial.available()){
    Serial.println("Waiting serial in serialInit()");
    delay(1e3);
  }
  serial_data = serial.readString();
  serial_data.trim();
  digitalWrite(serial_interrupt_pin, LOW);
  if(serial_data == "listening"){
    Serial.println("Return: TRUE");
    return true;
  }else{
    Serial.println("Return: FALSE");
    Serial.println("Return: TRUE");
  } 
}
// Functions to handle accident confirmation and cancelation Interrupts
void confirm(){
  if(serialInit()){
    serial.println(ACCIDENT);
    while(!serial.available()); // Wait for locaion data
    serial_data = serial.readString();
    serial_data.trim();
    jsonString = JSON.parse(serial_data);
    latitude = (double)jsonString["latitude"];
    longitude = (double)jsonString["longitude"];
  
    jsonObject["endpoint"] = "/api/confirm/";
    jsonObject["vehicle"] = vehicle_number;
    jsonObject["latitude"] = latitude;
    jsonObject["longitude"] = longitude;

    serialESP.listen();
    if(serialESP.isListening())
      serialESP.println(JSON.stringify(jsonObject));

    // Print into the serial
    Serial.println("Acident confirmed");
    Serial.println("Data " + JSON.stringify(jsonObject));
  }
}
void cancel(){ 
  serialESP.listen();
  serialESP.println("/api/cancel/" + vehicle_number); 
}


// Method to correct accident data and post
void postAccientData(){
  Serial.println("(postAccientData())Accident detected");
  if(serialInit()){
    serial.println(ACCIDENT);
    while(!serial.available()){
      Serial.println("Wait for location data");
      delay(1e3);
    } // Wait for locaion data
    serial_data = serial.readString();
    serial_data.trim();
    Serial.println("Serial location data: " + serial_data);

    jsonString = JSON.parse(serial_data);
    latitude = (double)jsonString["latitude"];
    longitude = (double)jsonString["longitude"];


    // Check gyroscopic value greater than others
    float gyrospcopic_data;
    if (roll > pitch) gyrospcopic_data = roll;
    else gyrospcopic_data = pitch;

    jsonObject["endpoint"] = "/api/create/";
    jsonObject["vehicle"] = vehicle_number;
    jsonObject["flame"] = digitalRead(flame_pin);
    jsonObject["smoke"] = analogSensor(smoke_pin);
    jsonObject["vibration"] = analogSensor(vibration_pin);
    jsonObject["gyroscope"] = gyrospcopic_data;
    jsonObject["latitude"] = latitude;
    jsonObject["longitude"] = longitude;
    jsonObject["brake"] = digitalRead(brake_pin);
    json_string = JSON.stringify(jsonObject);


    serialESP.listen();
    if(serialESP.isListening()){
      serialESP.println(json_string);
      while(!serialESP.available())
        Serial.println("Wait for ESP response");

      serial_data = serialESP.readString();
      serial_data.trim();
      Serial.println("serialESP data: " + serial_data);
      if(serial_data == "detected") digitalWrite(buzzer_pin, HIGH);
    }

    // Print into the serial
    Serial.println("Acident data posted");
    Serial.print("Data: ");
    Serial.println(json_string);
  }
}