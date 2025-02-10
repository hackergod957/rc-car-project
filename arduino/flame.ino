#include <SoftwareSerial.h>

SoftwareSerial bluetooth(10, 11); // RX, TX pins for Bluetooth communication

int flameSensorPin = A0; // Pin for the flame sensor
int flameThreshold = 300; // Threshold to consider fire detection
int flameValue = 0; // Variable to store the sensor reading

void setup() {
  Serial.begin(9600);  // Start serial communication
  bluetooth.begin(9600); // Start Bluetooth communication
  pinMode(flameSensorPin, INPUT); // Set the flame sensor pin as input
}

void loop() {
  flameValue = analogRead(flameSensorPin);  // Read flame sensor value

  // If the flame value exceeds the threshold, send data
  if (flameValue > flameThreshold) {
    bluetooth.print("FIRE:");
    bluetooth.println(flameValue); // Send the fire intensity
  } else {
    bluetooth.print("SAFE:0"); // No fire detected
    bluetooth.println();
  }
  
  delay(1000); // Delay for 1 second before reading again
}
