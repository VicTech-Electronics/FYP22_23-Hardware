#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

const char* server = "victonix-fyp.herokuapp.com";
const int httpsPort = 443;

WiFiClientSecure client;

// Decralation of useful varibles
String serial_data, requestBody, data_to_send;

// Method to post json data to the server
void postJSONData(String endpoint, String json_data){
  // Wait for a connection to be established
  if (WiFi.status() == WL_CONNECTED) {
    // Create the request body
    requestBody = "POST " + endpoint + " HTTP/1.1\r\n";
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
        if(line.indexOf("[") != -1) Serial.println(line);
      }client.stop();
    }
  } Serial.println("FAIL");
}

// Method to handle Delete equest
void postDeleteRequest(String endpoint){
  if (WiFi.status() == WL_CONNECTED) {
    // Create the request body
    requestBody = "GET " + endpoint + " HTTP/1.1\r\n";
    requestBody += "Host: " + String(server) + "\r\n";
    requestBody += "Content-Length: 0\r\n"; // No JSON data in the request body for DELETE
    requestBody += "\r\n";
    
    // Make the HTTPS request
    if (client.connect(server, httpsPort)) {
      client.print(requestBody);
      delay(500);

      // Read and print the response
      while (client.available()) {
        String line = client.readStringUntil('\r');
        if(line.indexOf("[") != -1) Serial.println(line);
      }client.stop();
    }
  }  Serial.println("FAIL");
}

void setup() {
  Serial.begin(9600);
  
  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }Serial.println("Connected to WiFi");

  Serial.println("Project start");
  
  // Set up the client
  client.setInsecure(); // Allow connections to SSL sites without valid certificates
}

void loop() {
  if(Serial.available()){
    serial_data = "";
    while(Serial.available()){
      serial_data += Serial.readString();
    } serial_data.trim();

    if(serial_data.indexOf("@") != -1){
      data_to_send = serial_data.substring(1);
      data_to_send.trim();
      postJSONData("/api/create/", data_to_send);
    }else if(serial_data.indexOf("#") != -1){
      data_to_send = serial_data.substring(1);
      data_to_send.trim();
      postJSONData("/api/confirm/", data_to_send);
    } else postDeleteRequest(serial_data);
  }
}