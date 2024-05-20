#include <Arduino.h>
#include "DHT.h"
#include "Adafruit_Sensor.h"
int analogpin;
int trigger1 = 5;
int trigger2 = 6;

int motionPin = 4;  // Pin connected to OUT of the PIR sensor
int motionState = LOW;  // By default, no motion is detected
int val = 0;  // Variable to store the read value from the sensor
#define DHTTYPE DHT11
int sensePin = 2;
/*creating the object*/
DHT HT(sensePin, DHTTYPE);
/*setting up variables for measuring humidity and temperature*/
float humidity;
float tempC;
float tempF;
int setTime = 500;
int dt = 1000;

void setup() {
  pinMode(motionPin, INPUT);  // Set the motionPin as input
  pinMode(trigger1, OUTPUT);
  pinMode(trigger2, OUTPUT);
  Serial.begin(9600);
  HT.begin();
  delay(setTime); 
  while (!Serial)
  {
    ;
  }

}

void loop() {

  humidity = HT.readHumidity();
  tempC = HT.readTemperature();
  tempF = HT.readTemperature(true);

  analogpin = analogRead(A4);
  Serial.print("light value: ");
  Serial.println(analogpin);
  delay(1000);

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("Temperature ");
  Serial.print(tempC);
  Serial.print(" c ");
  Serial.print(tempF);
  Serial.println(" F ");
  delay(dt);

  digitalWrite(trigger1, HIGH);
  digitalWrite(trigger1, HIGH);

  val = digitalRead(motionPin);  // Read the value from the sensor
  if (val == HIGH) {  // Check if the sensor output is HIGH
    if (motionState == LOW) {
      Serial.println("Motion detected!");  // Print motion detected message
      motionState = HIGH;  // Update the state to motion detected
      digitalWrite(trigger1, LOW);
      digitalWrite(trigger2, LOW);
    }
  }else{
    if (motionState == HIGH) {
      Serial.println("Motion ended!");  // Print motion ended message
      motionState = LOW;  // Update the state to no motion
      digitalWrite(trigger1, HIGH);
      digitalWrite(trigger2, HIGH);
    }
    digitalWrite(trigger1, HIGH);
    digitalWrite(trigger2, HIGH);
  }
  delay(100);  // Small delay to avoid serial monitor flooding
}
