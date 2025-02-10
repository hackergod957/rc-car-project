// Define sensor pins
const int trigPin1 = 9;  // Trigger pin for ultrasonic sensor
const int echoPin1 = 10; // Echo pin for ultrasonic sensor

unsigned long previousMillis = 0;   // Store the last time data was sent
const long interval = 1000;          // Interval between data sends (in milliseconds)

void setup() {
  Serial.begin(115200);  // Match with ESP32 baud rate
  
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    // Measure distance from the single sensor
    long distance1 = getDistance(trigPin1, echoPin1);

    // Send only one distance value
    Serial.println(String(distance1));
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
