#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <Arduino_JSON.h>

const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

const char* server = "victonix-fyp.herokuapp.com";
const int httpsPort = 443;

WiFiClientSecure client;

// Decralation of useful varibles
JSONVar json_object, modified_json_object;
String serial_data, json_string, endPoint, requestBody;

// Method to receive server response
String serverResponse(){
  // Make the HTTPS request
  if (client.connect(server, httpsPort)) {
    client.print(requestBody);
    delay(500);
    // Read and print the response
    while (client.available()) {
      String line = client.readStringUntil('\r');
      if(line.indexOf("[") != -1) return line
    }client.stop();
  }
  return "Fail";
}

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
    
    Serial.println(serverResponse());
  }
}

// Method to handle Delete equest
void postDeleteRequest(String endpoint){
  if (WiFi.status() == WL_CONNECTED) {
    // Create the request body
    requestBody = "DELETE " + endpoint + " HTTP/1.1\r\n";
    requestBody += "Host: " + String(server) + "\r\n";
    requestBody += "Content-Length: 0\r\n"; // No JSON data in the request body for DELETE
    requestBody += "\r\n";
    
    Serial.println(serverResponse());
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

  Serial.println("Project start");
  
  // Set up the client
  client.setInsecure(); // Allow connections to SSL sites without valid certificates
}

void loop() {
  while(!Serial.available()); // Wait for the data in serial buffer
  serial_data = Serial.readString();
  serial_data.trim();
  
  if(serial_data.indexOf("{") != -1){
    json_object = JSON.parse(serial_data);
    JSONVar keys = json_object.keys(); // Get the keys of the original JSON object
    for(byte i=0; i<json_object.length(); i++){
      String key = keys[i];
      if(key != "endpoint")
        modified_json_object[key] = json_object[key];
      else endPoint = (const char*)json_object["endpoint"];
    }
    json_string = JSON.stringify(modified_json_object);
    postJSONData(endPoint, json_string);
  }else postDeleteRequest(serial_data);
}