#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Replace with your server URL and port
const char* serverURL = "jesca-fyp22-23.herokuapp.com";
const int serverPort = 443;

// Create an instance of WiFiClientSecure to establish a secure connection
WiFiClientSecure client;

// Method to send data
String postData(String data){
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverURL, serverPort)) {
      client.print(String("POST /api/payment/ HTTP/1.1\r\n") +
                  "Host: " + serverURL + "\r\n" +
                  "Content-Type: application/json\r\n" +
                  "Content-Length: " + data.length() + "\r\n" +
                  "Connection: close\r\n\r\n" +
                  data);

      while (client.connected()) {
        if (client.available()) {
          String response = client.readStringUntil('\r');
          if(response.indexOf("\"") != -1) return response;
        }
      } client.stop();
    }
  } return "Fail";
}

void setup() {
  Serial.begin(9600);
  delay(100);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setInsecure();
}

void loop() {
  while(!Serial.available()){
    String serial_data = Serial.readString();
    serial_data.trim();
    String payload = postData(serial_data);
    Serial.println(payload);
  }
}
