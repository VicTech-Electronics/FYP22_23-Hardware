#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Create an instance of WiFiClient0 to establish connection
WiFiClient client;
HTTPClient http;

void postData(String string_data){
  if(WiFi.status() == WL_CONNECTED){
   http.begin(client, "http://161.35.210.153:8000/device-update-portal");
   http.addHeader("Content-Type", "application/json");

   int httpCode = http.POST(string_data);
   String payload = http.getString();

   if(httpCode == HTTP_CODE_OK) Serial.println(payload);
   else Serial.println("Error: " + http.errorToString(httpCode));

   string_data = "" ; payload = "";
   http.end();
 }
}

void setup() {
  Serial.begin(9600);
  delay(3e3);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println("CONNECTED");

}

void loop() {
  while(!Serial.available());
  String serial_data = Serial.readString();
  postData(serial_data);
}
