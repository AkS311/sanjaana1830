#include <Ultrasonic.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

// Define constants for Wi-Fi
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Define constants for IBM IoT Platform
const char* iotServer = "YOUR_IOT_SERVER";
const int iotPort = 8883;
const char* iotUsername = "YOUR_IOT_USERNAME";
const char* iotPassword = "YOUR_IOT_PASSWORD";
const char* iotClientId = "YOUR_IOT_CLIENT_ID";
const char* iotTopic = "iot-2/evt/status/fmt/json";

// Define constants for ultrasonic sensor
const int trigPin = 2;
const int echoPin = 3;

WiFiClientSecure wifiClient;
PubSubClient mqttClient(wifiClient);
Ultrasonic ultrasonic(trigPin, echoPin);

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Configure MQTT client
  mqttClient.setServer(iotServer, iotPort);
}

void loop() {
  if (!mqttClient.connected()) {
    reconnect();
  }

  // Measure the distance
  long duration = ultrasonic.timing();
  int distance = ultrasonic.convert(distance, Ultrasonic::CM);

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  if (distance < 100) {
    // Prepare payload
    StaticJsonDocument<100> jsonDoc;
    jsonDoc["distance"] = distance;
    char payload[100];
    serializeJson(jsonDoc, payload);

    // Publish payload to IBM IoT Platform
    mqttClient.publish(iotTopic, payload);
  }

  delay(1000);
}

void reconnect() {
  while (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");

    if (mqttClient.connect(iotClientId, iotUsername, iotPassword)) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" Retrying in 5 seconds...");
      delay(5000);
    }
  }
}
