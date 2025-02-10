#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi credentials
const char* ssid = "cybermystic_2.4";          // Replace with your Wi-Fi SSID
const char* password = "Cyber@mystic_007";     // Replace with your Wi-Fi password

// Flask API endpoint
const String flask_url = "http://192.168.1.16:5000/map"; // Replace with your Flask server's IP address

void setup() {
  Serial.begin(115200); // Match with Arduino's baud rate

  // Connect to Wi-Fi
  Serial.println("Connecting to Wi-Fi...");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }
  
  Serial.println("Connected to Wi-Fi!");
}

void loop() {
  if (Serial.available() > 0) {
    String sensorData = Serial.readStringUntil('\n');  // Read the data until newline
    
    // Extract the data for just one sensor (e.g., distance1)
    int separator = sensorData.indexOf(","); // Looking for the first separator
    String distance1 = sensorData.substring(0, separator); // Extract the first sensor data
    
    // Print the sensor data to Serial Monitor
    Serial.print("Sensor Data: ");
    Serial.println(distance1);
    
    // Send the data to Flask server
    sendDataToFlask(distance1);
    
    delay(2000);  // Delay between sending data
  }
}

void sendDataToFlask(String distance1) {
  if (WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;
    
    http.begin(client, flask_url);  // Begin HTTP request
    http.addHeader("Content-Type", "application/json");

    // Create JSON object to send
    String jsonData = "{\"distance1\": " + distance1 + "}";

    // Send the POST request
    int httpResponseCode = http.POST(jsonData);

    // Handle the response
    if (httpResponseCode > 0) {
      Serial.println("Data sent successfully");
      Serial.println("Response Code: " + String(httpResponseCode));
    } else {
      Serial.println("Failed to send data");
    }

    // End the HTTP request
    http.end();
  } else {
    Serial.println("WiFi not connected");
  }
}
