#include <Arduino.h>

const int relayPin = 2;
const int currentSensorPin = A0;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relayPin, HIGH); // Turn on the relay
  delay(2000); // Keep the relay on for 2 seconds

  int sensorValue = analogRead(currentSensorPin); // Read current sensor value
  float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage
  float current = (voltage - 2.5) / 0.066; // Convert voltage to current for ACS712-5A sensor

  Serial.print("Current: ");
  Serial.print(current);
  Serial.println(" A");

  digitalWrite(relayPin, LOW); // Turn off the relay
  delay(2000); // Keep the relay off for 2 seconds
}
