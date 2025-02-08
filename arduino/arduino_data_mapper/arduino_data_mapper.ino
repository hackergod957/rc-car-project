// Define sensor pins
const int trigPin1 = 9; // Trigger pin for ultrasonic sensor 1
const int echoPin1 = 10; // Echo pin for ultrasonic sensor 1
const int trigPin2 = 11; // Trigger pin for ultrasonic sensor 2
const int echoPin2 = 12; // Echo pin for ultrasonic sensor 2
const int trigPin3 = 13; // Trigger pin for ultrasonic sensor 3
const int echoPin3 = 14; // Echo pin for ultrasonic sensor 3

unsigned long previousMillis = 0;   // Store the last time data was sent
const long interval = 1000;          // Interval between data sends (in milliseconds)

void setup() {
  // Initialize serial communication
  Serial.begin(9600); // This baud rate should match the ESP32 code
  
  // Initialize sensor pins
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if the interval has passed (1 second)
  if (currentMillis - previousMillis >= interval) {
    // Save the last time data was sent
    previousMillis = currentMillis;

    // Measure distance for each sensor
    long distance1 = getDistance(trigPin1, echoPin1);
    long distance2 = getDistance(trigPin2, echoPin2);
    long distance3 = getDistance(trigPin3, echoPin3);

    // Send the distances as a comma-separated string
    String data = String(distance1) + "," + String(distance2) + "," + String(distance3);
    
    // Send the data to the ESP32
    Serial.println(data);
  }
}

// Function to measure distance using ultrasonic sensor
long getDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration / 2) * 0.0344; // Convert time to distance (cm)
  
  return distance;
}
