#include <WiFi.h>
#include <HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "Your_SSID";          // Replace with your Wi-Fi SSID
const char* password = "Your_PASSWORD";  // Replace with your Wi-Fi password

// Flask API endpoint
const String flask_url = "http://127.0.0.1:5000/map"; // Replace with your Flask server's IP address

void setup() {
  // Initialize Serial communication
  Serial.begin(9600);  // Baud rate for Arduino communication (match with Arduino)

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  
  // Wait until the ESP32 is connected to Wi-Fi
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  
  Serial.println("Connected to Wi-Fi!");
}

void loop() {
  // Check if data is available from Arduino
  if (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n');  // Read the data until newline
    
    // Split the data (e.g., distance1, distance2, distance3)
    int separator1 = sensorData.indexOf(",");
    int separator2 = sensorData.indexOf(",", separator1 + 1);
    
    String distance1 = sensorData.substring(0, separator1);
    String distance2 = sensorData.substring(separator1 + 1, separator2);
    String distance3 = sensorData.substring(separator2 + 1);
    
    // Send the data to Flask server via HTTP POST
    sendDataToFlask(distance1, distance2, distance3);
    
    delay(2000);  // Send data every 2 seconds
  }
}

void sendDataToFlask(String distance1, String distance2, String distance3) {
  // Create a JSON object to send to the Flask server
  String jsonData = "{\"distance1\": " + distance1 + ", \"distance2\": " + distance2 + ", \"distance3\": " + distance3 + "}";

  // Make an HTTP POST request to the Flask server
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    
    // Set the target URL and content type
    http.begin(flask_url);
    http.addHeader("Content-Type", "application/json");

    // Send the HTTP POST request with the sensor data
    int httpResponseCode = http.POST(jsonData);
    
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully to Flask server");
      Serial.println("Response Code: " + String(httpResponseCode));
    } else {
      Serial.println("Error sending data to Flask server");
      Serial.println("Error Code: " + String(httpResponseCode));
    }

    // End the HTTP request
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
