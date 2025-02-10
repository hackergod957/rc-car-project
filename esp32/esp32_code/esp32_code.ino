#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

// Wi-Fi credentials (not needed anymore for sensor-only use)
const char* ssid = "cybermystic_2.4";          // Replace with your Wi-Fi SSID
const char* password = "Cyber@mystic_007";   // Replace with your Wi-Fi password

// Pins for Ultrasonic Sensor
const int trigPin = D2;  // Change this as per your wiring
const int echoPin = D1;  // Change this as per your wiring

// Variables for time-based data sending
unsigned long previousMillis = 0;
const long interval = 2000;  // 2 seconds interval to take data

void setup() {
  Serial.begin(115200);  // Start Serial Monitor
  
  // Connect to Wi-Fi (not needed for sensor-only mode, but left in case you want to use Wi-Fi in the future)
  WiFi.begin(ssid, password); // Connect to Wi-Fi

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to Wi-Fi...");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Take data every 2 seconds without using delay
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Update the last time data was taken
    
    // Measure distance from ultrasonic sensor
    long duration, distance;
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    
    duration = pulseIn(echoPin, HIGH);
    distance = (duration / 2) / 29.1;  // Convert duration to distance in cm
    
    Serial.print("Distance: ");
    Serial.println(distance);  // Display the distance in the Serial Monitor
  }
}
