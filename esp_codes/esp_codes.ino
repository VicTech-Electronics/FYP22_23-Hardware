#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Replace with your server URL and port
const char* serverURL = "nmalabacropr.onrender.com";
const int serverPort = 443;

// Create an instance of WiFiClientSecure to establish a secure connection
WiFiClientSecure client;

// Method to send request
void request(String data){
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverURL, serverPort)) {
      // Make an HTTPS GET request
      client.print(String("GET /predict-app/process_data/" + data + "/ HTTP/1.1\r\n") +
                   "Host: " + serverURL + "\r\n" +
                   "Connection: close\r\n\r\n");

      Serial.println("Sending GET request...");

      // Wait for the server's response
      while (client.connected()) {
        if (client.available()) {
          String response = client.readStringUntil('\r');
          Serial.println(response);
        }
      }

      // Disconnect from the server
      client.stop();
      Serial.println("Request complete");
    } else {
      Serial.println("Connection to server failed");
    }
  }
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

  // Allow insecure HTTPS connection
  client.setInsecure();
}

void loop() {
  while(!Serial.available());
  String serial_data = Serial.readString();
  serial_data.trim();
  Serial.println("ESP data: " + serial_data);
  request(serial_data);
}