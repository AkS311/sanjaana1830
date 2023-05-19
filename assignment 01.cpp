// Include necessary libraries
#include <Servo.h>

// Define constants for sensor pins
const int pirPin = 2;        // PIR sensor pin
const int tempPin = A0;      // Temperature sensor pin

// Define constants for actuator pins
const int ledPin = 3;        // LED pin
const int buzzerPin = 4;     // Buzzer pin
const int servoPin = 5;      // Servo motor pin

// Define variables
int tempValue = 0;           // Temperature value
int pirState = LOW;          // PIR sensor state
int previousPirState = LOW;  // Previous PIR sensor state
Servo doorLock;              // Servo motor object

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);

  // Set the sensor pins as input
  pinMode(pirPin, INPUT);
  pinMode(tempPin, INPUT);

  // Set the actuator pins as output
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  doorLock.attach(servoPin);

  // Move the servo motor to the initial position (locked)
  doorLock.write(0);
}

void loop() {
  // Read temperature value from the sensor
  tempValue = analogRead(tempPin);

  // Convert temperature value to Celsius
  float celsius = map(tempValue, 0, 1023, -40, 125);

  // Print temperature value to serial monitor
  Serial.print("Temperature: ");
  Serial.print(celsius);
  Serial.println("°C");

  // Read PIR sensor state
  pirState = digitalRead(pirPin);

  // Check if the PIR state has changed
  if (pirState != previousPirState) {
    // If motion is detected
    if (pirState == HIGH) {
      digitalWrite(ledPin, HIGH);     // Turn on the LED
      tone(buzzerPin, 1000);           // Sound the buzzer
      doorLock.write(90);              // Unlock the door
      delay(500);                      // Wait for half a second
      doorLock.write(0);               // Lock the door
      delay(500);                      // Wait for half a second
    }
    else {
      digitalWrite(ledPin, LOW);      // Turn off the LED
      noTone(buzzerPin);               // Stop the buzzer
    }
    previousPirState = pirState;       // Update the previous PIR state
  }
}
