#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Replace with your server URL and port
const char* serverURL = "hospitalmanagement-fyp22-23.herokuapp.com";
const int serverPort = 443;

// Create an instance of WiFiClientSecure to establish a secure connection
WiFiClientSecure client;

// method to post data
void sendRequest(String command){
  String method, end_point;
  if(command == "request"){
    method = "POST ";
    end_point = "/api/request/";
  }else if(command == "response"){
    method = "PUT ";
    end_point = "/api/response/";
  }

  String json_data = "{\"device\":\"New Device\"}";
  if (WiFi.status() == WL_CONNECTED) {
    if (client.connect(serverURL, serverPort)) {
      // Make an HTTPS POST request
      client.print(String(method + end_point + " HTTP/1.1\r\n") +
                   "Host: " + serverURL + "\r\n" +
                   "Content-Type: application/json\r\n" +
                   "Content-Length: " + json_data.length() + "\r\n" +
                   "Connection: close\r\n\r\n" +
                   json_data);

      Serial.println("Sending JSON data...");

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
  String serial_data = Serial.readStringUntil('\r');
  serial_data.trim();
  sendRequest(serial_data);
}
