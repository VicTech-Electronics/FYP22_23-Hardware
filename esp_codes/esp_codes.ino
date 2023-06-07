#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

const char* server = "sebabotire-fyp22-23.herokuapp.com";
const int httpsPort = 443;

WiFiClientSecure client;

// Decralation of useful variables
String serial_data;

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to WiFi");
  
  // Set up the client
  client.setInsecure(); // Allow connections to SSL sites without valid certificates
}

void loop() {
  // Wait for a connection to be established
  if (WiFi.status() == WL_CONNECTED) {
    // Create the request
    String request = "GET /api/get/ HTTP/1.1\r\n";
    request += "Host: " + String(server) + "\r\n";
    request += "Connection: close\r\n";
    request += "\r\n";
    
    // Make the HTTPS request
    if (client.connect(server, httpsPort)) {
      client.print(request);
      delay(500);
      
      // Read and print the response
      while (client.available()) {
        String line = client.readStringUntil('\r');
        if(line.indexOf("{") != -1) serial_data = line;
      }

      JSONVar jsonObject = JSON.parse(serial_data);
      serial_data = (const char*)jsonObject["state"];
      Serial.println(serial_data);
      
      client.stop();
    }
  }
  
  delay(3e3); // Wait for 5 seconds before sending the next request
}
