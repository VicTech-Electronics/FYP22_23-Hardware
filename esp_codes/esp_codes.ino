#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Replace with your server URL and port
const char* serverURL = "chibu-fyp22-23-fd8685b2b409.herokuapp.com";
const int serverPort = 443;

// Create an instance of WiFiClientSecure to establish a secure connection
WiFiClientSecure client;

// Method to post data
void postData(String end_point, String json_data){
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverURL, serverPort)) {
      // Make an HTTPS POST request
      client.print(String("POST "  + end_point + " HTTP/1.1\r\n") +
                   "Host: " + serverURL + "\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: " + json_data.length() + "\r\n" +
                   "Connection: close\r\n\r\n" +
                   json_data);

      // Wait for the server's response
      while (client.connected()) {
        if (client.available()) {
          String response = client.readStringUntil('\r');
          if (response.indexOf("[") != -1){
            Serial.println(response);
            return;
          } 
        }
      }
      // Disconnect from the server
      client.stop();
    }
  }

  Serial.println("ESP found no data");
}

void setup() {
  Serial.begin(9600);
  delay(100);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  } Serial.println("CONNECTED");

  // Allow insecure HTTPS connection
  client.setInsecure();
}

void loop() {
  while(!Serial.available());
  String serial_data = Serial.readString();
  postData("/api/service/", serial_data);
}
