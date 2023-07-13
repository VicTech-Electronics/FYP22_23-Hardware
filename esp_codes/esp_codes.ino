#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Replace with your network credentials
const char* ssid = "VicTech Electronics";
const char* password = "#Electronics98";

// Replace with your server URL and port
const char* serverURL = "161.35.210.153";
const int serverPort = 8000;

// Create an instance of WiFiClient0 to establish connection
WiFiClient client;

// Decralation of usefull variables
String end_point = "/device-update-portal";

// Method to post data
void postData(String json_data){
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
          Serial.println(response);
        }
      }
      // Disconnect from the server
      client.stop();
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
}

void loop() {
  while(!Serial.available());
  String serial_data = Serial.readString();
  postData(serial_data);
}
