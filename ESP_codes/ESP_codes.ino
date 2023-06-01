#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <FirebaseHttpClient.h>
#include <Firebase.h>

// Set your Firebase credentials
#define FIREBASE_HOST "your-firebase-project.firebaseio.com"
#define FIREBASE_AUTH "your-firebase-auth-token"

// Set your Wi-Fi credentials
const char* WIFI_SSID = "your-ssid";
const char* WIFI_PASSWORD = "your-password";

JSONVar jsonObject;

// Method to read data from Firebase
String readData(){
  float packing = Firebase.getInt("packing_started/status");
  float payment = Firebase.getInt("payment_status/status");

  jsonObject["packing"] = packing;
  jsonObject["payment"] = payment;
  
  return JSON.stringify(jsonObject);
}

// Method to post data to Firebase
void postData(){
  if(Serial.available()){
    String data = Serial.readString();
    jsonObject = JSON.parse(data);

    Firebase.setBool("slots_status/slot1Status", (bool)jsonObject["slot1Status"]);
    Firebase.setBool("slots_status/slot2Status", (bool)jsonObject["slot2Status"]);
    Firebase.setBool("slots_status/slot3Status", (bool)jsonObject["slot3Status"]);
  }
}

void setup() {
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } Serial.println("Connected to Wi-Fi");
  Serial.begin(9600);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}
void loop() {
  readData();
  postData();
}