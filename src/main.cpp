#include <Arduino.h>

const int relayPin = 2;
const int currentSensorPin = A5;
bool relayState = false;

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  digitalWrite(relayPin, HIGH); // Ensure relay is off initially
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'O') { // Command to turn relay ON
      relayState = true;
      digitalWrite(relayPin, LOW); // Turn on the relay
      Serial.println("Relay ON");
    } else if (command == 'F') { // Command to turn relay OFF
      relayState = false;
      digitalWrite(relayPin, HIGH); // Turn off the relay
      Serial.println("Relay OFF");
    } else if (command == 'C') { // Command to read current
      int sensorValue = analogRead(currentSensorPin); // Read current sensor value
      float voltage = sensorValue * (5.0 / 1023.0); // Convert to voltage
      float current = (voltage - 2.5) / 0.066; // Convert voltage to current for ACS712-5A sensor
      Serial.print("Current: ");
      Serial.print(current);
      Serial.println(" A");
    }
  }
}
