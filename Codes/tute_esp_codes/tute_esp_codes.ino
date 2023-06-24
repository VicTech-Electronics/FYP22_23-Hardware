#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

const char* server = "tute-fyp22-23.herokuapp.com";
const int httpsPort = 443;

WiFiClientSecure client;

// Decralation of useful varibles
JSONVar json_object, modified_json_object;
String serial_data, endPoint, requestBody;


// Method to post json data to the server
void postJSONData(String json_data){
  // Wait for a connection to be established
  if (WiFi.status() == WL_CONNECTED) {
    // Create the request body
    requestBody = "POST /api/info/ HTTP/1.1\r\n";
    requestBody += "Host: " + String(server) + "\r\n";
    requestBody += "Content-Type: application/json\r\n";
    requestBody += "Content-Length: " + String(json_data.length()) + "\r\n";
    requestBody += "\r\n";
    requestBody += json_data;
    
    // Make the HTTPS request
    if (client.connect(server, httpsPort)) {
      client.print(requestBody);
      delay(500);

      // Read and print the response
      while (client.available()) {
        String line = client.readStringUntil('\r');
        Serial.println(line);
      }client.stop();
    }
  }
}


void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }Serial.println("Connected to WiFi");
  
  // Set up the client
  client.setInsecure(); // Allow connections to SSL sites without valid certificates
}

void loop() {
  while(!Serial.available()); // Wait for the data in serial buffer
  serial_data = Serial.readString();
  serial_data.trim();
  postJSONData(serial_data);
}