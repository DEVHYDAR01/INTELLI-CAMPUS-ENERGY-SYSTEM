#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define DHTTYPE DHT11    // DHT 11
const int DHTPIN = 2;    // GPIO pin for DHT11 sensor
const int RELAY1_PIN = 6; // GPIO pin for Relay 1 (Bulb)
const int RELAY2_PIN = 3; // GPIO pin for Relay 2 (Socket)
const int RELAY3_PIN = 4; // GPIO pin for Relay 3 (Fan)
const int CURRENT_SENSOR_PIN1 = A5; // GPIO pin for Current Sensor 1 (bulb)
const int CURRENT_SENSOR_PIN2 = A4; // GPIO pin for Current Sensor 2 (socket)
const int CURRENT_SENSOR_PIN3 = A3; // GPIO pin for Current Sensor 3 (fan)
const int MOTION_SENSOR_PIN = 5; // GPIO pin for Motion Sensor
const int LIGHT_SENSOR_PIN = A0; // GPIO pin for Light Sensor

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(RELAY1_PIN, OUTPUT);
  pinMode(RELAY2_PIN, OUTPUT);
  pinMode(RELAY3_PIN, OUTPUT);
  pinMode(MOTION_SENSOR_PIN, INPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  Serial.begin(9600);
  dht.begin();
  digitalWrite(RELAY1_PIN, HIGH); // Ensure relay 1 is off initially
  digitalWrite(RELAY2_PIN, HIGH); // Ensure relay 2 is off initially
  digitalWrite(RELAY3_PIN, HIGH); // Ensure relay 3 is off initially
}

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();
    if (command == 'O') { // Command to turn relay 1 ON
      digitalWrite(RELAY1_PIN, LOW); // Turn on relay 1
      Serial.println("Relay 1 ON");
    } else if (command == 'F') { // Command to turn relay 1 OFF
      digitalWrite(RELAY1_PIN, HIGH); // Turn off relay 1
      Serial.println("Relay 1 OFF");
    } else if (command == 'A') { // Command to turn relay 2 ON
      digitalWrite(RELAY2_PIN, LOW); // Turn on relay 2
      Serial.println("Relay 2 ON");
    } else if (command == 'B') { // Command to turn relay 2 OFF
      digitalWrite(RELAY2_PIN, HIGH); // Turn off relay 2
      Serial.println("Relay 2 OFF");
    } else if (command == 'C') { // Command to turn relay 3 ON
      digitalWrite(RELAY3_PIN, LOW); // Turn on relay 3
      Serial.println("Relay 3 ON");
    } else if (command == 'D') { // Command to turn relay 3 OFF
      digitalWrite(RELAY3_PIN, HIGH); // Turn off relay 3
      Serial.println("Relay 3 OFF");
    }
  }

  // Read current sensor values
  int sensorValue1 = analogRead(CURRENT_SENSOR_PIN1);
  float voltage1 = sensorValue1 * (5.0 / 1023.0); // Convert to voltage
  float current1 = (voltage1 - 2.5) / 0.066; // Convert voltage to current for ACS712-5A sensor

  int sensorValue2 = analogRead(CURRENT_SENSOR_PIN2);
  float voltage2 = sensorValue2 * (5.0 / 1023.0);
  float current2 = (voltage2 - 2.5) / 0.066;

  int sensorValue3 = analogRead(CURRENT_SENSOR_PIN3);
  float voltage3 = sensorValue3 * (5.0 / 1023.0);
  float current3 = (voltage3 - 2.5) / 0.066;

  // Read temperature and humidity
  float humidity = dht.readHumidity();
  float tempC = dht.readTemperature();
  float tempF = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Send data to serial for Arduino IoT Cloud
  Serial.print("current1 ");
  Serial.println(current1);
  Serial.print("current2 ");
  Serial.println(current2);
  Serial.print("current3 ");
  Serial.println(current3);
  Serial.print("humidity ");
  Serial.println(humidity);
  Serial.print("temperatureC ");
  Serial.println(tempC);
  Serial.print("temperatureF ");
  Serial.println(tempF);

  delay(2000); // Wait a few seconds between measurements
}





















































// #include <Arduino.h>
// #include <Adafruit_Sensor.h>
// #include "DHT.h"

// #define DHTTYPE DHT11    // DHT 11
// const int DHTPIN = 2;    // GPIO pin for DHT11 sensor
// const int RELAY1_PIN = 6; // GPIO pin for Relay 1
// const int RELAY2_PIN = 3; // GPIO pin for Relay 2
// const int RELAY3_PIN = 4; // GPIO pin for Relay 3
// const int CURRENT_SENSOR_PIN1 = A5; // GPIO pin for Current Sensor 1 (bulb)
// const int CURRENT_SENSOR_PIN2 = A4; // GPIO pin for Current Sensor 2 (socket)
// const int CURRENT_SENSOR_PIN3 = A3; // GPIO pin for Current Sensor 3 (fan)

// DHT dht(DHTPIN, DHTTYPE);

// void setup() {
//   pinMode(RELAY1_PIN, OUTPUT);
//   pinMode(RELAY2_PIN, OUTPUT);
//   pinMode(RELAY3_PIN, OUTPUT);
//   Serial.begin(9600);
//   dht.begin();
//   digitalWrite(RELAY1_PIN, HIGH); // Ensure relay 1 is off initially
//   digitalWrite(RELAY2_PIN, HIGH); // Ensure relay 2 is off initially
//   digitalWrite(RELAY3_PIN, HIGH); // Ensure relay 3 is off initially
// }

// void loop() {
//   if (Serial.available() > 0) {
//     char command = Serial.read();
//     if (command == 'O') { // Command to turn relay 1 ON
//       digitalWrite(RELAY1_PIN, LOW); // Turn on relay 1
//       Serial.println("Relay 1 ON");
//     } else if (command == 'F') { // Command to turn relay 1 OFF
//       digitalWrite(RELAY1_PIN, HIGH); // Turn off relay 1
//       Serial.println("Relay 1 OFF");
//     } else if (command == 'A') { // Command to turn relay 2 ON
//       digitalWrite(RELAY2_PIN, LOW); // Turn on relay 2
//       Serial.println("Relay 2 ON");
//     } else if (command == 'B') { // Command to turn relay 2 OFF
//       digitalWrite(RELAY2_PIN, HIGH); // Turn off relay 2
//       Serial.println("Relay 2 OFF");
//     } else if (command == 'C') { // Command to turn relay 3 ON
//       digitalWrite(RELAY3_PIN, LOW); // Turn on relay 3
//       Serial.println("Relay 3 ON");
//     } else if (command == 'D') { // Command to turn relay 3 OFF
//       digitalWrite(RELAY3_PIN, HIGH); // Turn off relay 3
//       Serial.println("Relay 3 OFF");
//     }
//   }

//   // Read current sensor values
//   int sensorValue1 = analogRead(CURRENT_SENSOR_PIN1);
//   float voltage1 = sensorValue1 * (5.0 / 1023.0); // Convert to voltage
//   float current1 = (voltage1 - 2.5) / 0.066; // Convert voltage to current for ACS712-5A sensor

//   int sensorValue2 = analogRead(CURRENT_SENSOR_PIN2);
//   float voltage2 = sensorValue2 * (5.0 / 1023.0);
//   float current2 = (voltage2 - 2.5) / 0.066;

//   int sensorValue3 = analogRead(CURRENT_SENSOR_PIN3);
//   float voltage3 = sensorValue3 * (5.0 / 1023.0);
//   float current3 = (voltage3 - 2.5) / 0.066;

//   // Read temperature and humidity
//   float humidity = dht.readHumidity();
//   float tempC = dht.readTemperature();
//   float tempF = dht.readTemperature(true);

//   // Check if any reads failed and exit early (to try again).
//   if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
//     Serial.println("Failed to read from DHT sensor!");
//     return;
//   }

//   // Send data to serial for Arduino IoT Cloud
//   Serial.print("current1 ");
//   Serial.println(current1);
//   Serial.print("current2 ");
//   Serial.println(current2);
//   Serial.print("current3 ");
//   Serial.println(current3);
//   Serial.print("humidity ");
//   Serial.println(humidity);
//   Serial.print("temperatureC ");
//   Serial.println(tempC);
//   Serial.print("temperatureF ");
//   Serial.println(tempF);

//   delay(2000); // Wait a few seconds between measurements
// }




























































// // #include <Arduino.h>
// // #include <Adafruit_Sensor.h>
// // #include "DHT.h"

// // const int RELAY1_PIN = 6; // GPIO pin for Relay 1
// // const int RELAY2_PIN = 3; // GPIO pin for Relay 2
// // const int RELAY3_PIN = 4; // GPIO pin for Relay 3
// // const int CURRENT_SENSOR_PIN1 = A5; // GPIO pin for Current Sensor 1 (bulb)
// // const int CURRENT_SENSOR_PIN2 = A4; // GPIO pin for Current Sensor 2 (socket)
// // const int CURRENT_SENSOR_PIN3 = A3; // GPIO pin for Current Sensor 3 (fan)

// // void setup() {
// //   pinMode(RELAY1_PIN, OUTPUT);
// //   pinMode(RELAY2_PIN, OUTPUT);
// //   pinMode(RELAY3_PIN, OUTPUT);
// //   Serial.begin(9600);
// //   digitalWrite(RELAY1_PIN, HIGH); // Ensure relay 1 is off initially
// //   digitalWrite(RELAY2_PIN, HIGH); // Ensure relay 2 is off initially
// //   digitalWrite(RELAY3_PIN, HIGH); // Ensure relay 3 is off initially
// // }

// // void loop() {
// //   if (Serial.available() > 0) {
// //     char command = Serial.read();
// //     if (command == 'O') { // Command to turn relay 1 ON
// //       digitalWrite(RELAY1_PIN, LOW); // Turn on relay 1
// //       Serial.println("Relay 1 ON");
// //     } else if (command == 'F') { // Command to turn relay 1 OFF
// //       digitalWrite(RELAY1_PIN, HIGH); // Turn off relay 1
// //       Serial.println("Relay 1 OFF");
// //     } else if (command == 'A') { // Command to turn relay 2 ON
// //       digitalWrite(RELAY2_PIN, LOW); // Turn on relay 2
// //       Serial.println("Relay 2 ON");
// //     } else if (command == 'B') { // Command to turn relay 2 OFF
// //       digitalWrite(RELAY2_PIN, HIGH); // Turn off relay 2
// //       Serial.println("Relay 2 OFF");
// //     } else if (command == 'C') { // Command to turn relay 3 ON
// //       digitalWrite(RELAY3_PIN, LOW); // Turn on relay 3
// //       Serial.println("Relay 3 ON");
// //     } else if (command == 'D') { // Command to turn relay 3 OFF
// //       digitalWrite(RELAY3_PIN, HIGH); // Turn off relay 3
// //       Serial.println("Relay 3 OFF");
// //     }
// //   }

// //   // Read current sensor values
// //   int sensorValue1 = analogRead(CURRENT_SENSOR_PIN1);
// //   float voltage1 = sensorValue1 * (5.0 / 1023.0); // Convert to voltage
// //   float current1 = (voltage1 - 2.5) / 0.066; // Convert voltage to current for ACS712-5A sensor

// //   int sensorValue2 = analogRead(CURRENT_SENSOR_PIN2);
// //   float voltage2 = sensorValue2 * (5.0 / 1023.0);
// //   float current2 = (voltage2 - 2.5) / 0.066;

// //   int sensorValue3 = analogRead(CURRENT_SENSOR_PIN3);
// //   float voltage3 = sensorValue3 * (5.0 / 1023.0);
// //   float current3 = (voltage3 - 2.5) / 0.066;

// //   // Send data to serial for Arduino IoT Cloud
// //   Serial.print("current1 ");
// //   Serial.println(current1);
// //   Serial.print("current2 ");
// //   Serial.println(current2);
// //   Serial.print("current3 ");
// //   Serial.println(current3);

// //   delay(2000); // Wait a few seconds between measurements
// // }





































// // #define DHTTYPE DHT11    // DHT 11
// // const int DHTPIN = 2;       // GPIO pin for DHT11 sensor
// // const int RELAY1_PIN = 6; // GPIO pin for Relay 1
// // const int RELAY2_PIN = 3; // GPIO pin for Relay 2
// // const int RELAY3_PIN = 4; // GPIO pin for Relay 3

// // DHT dht(DHTPIN, DHTTYPE);

// // void setup() {
// //   pinMode(RELAY1_PIN, OUTPUT);
// //   pinMode(RELAY2_PIN, OUTPUT);
// //   pinMode(RELAY3_PIN, OUTPUT);
// //   Serial.begin(9600);
// //   dht.begin();
// //   digitalWrite(RELAY1_PIN, HIGH); // Ensure relay 1 is off initially
// //   digitalWrite(RELAY2_PIN, HIGH); // Ensure relay 2 is off initially
// //   digitalWrite(RELAY3_PIN, HIGH); // Ensure relay 3 is off initially
// // }

// // void loop() {
// //   if (Serial.available() > 0) {
// //     char command = Serial.read();
// //     if (command == 'O') { // Command to turn relay 1 ON
// //       digitalWrite(RELAY1_PIN, LOW); // Turn on relay 1
// //       Serial.println("Relay 1 ON");
// //     } else if (command == 'F') { // Command to turn relay 1 OFF
// //       digitalWrite(RELAY1_PIN, HIGH); // Turn off relay 1
// //       Serial.println("Relay 1 OFF");
// //     } else if (command == 'A') { // Command to turn relay 2 ON
// //       digitalWrite(RELAY2_PIN, LOW); // Turn on relay 2
// //       Serial.println("Relay 2 ON");
// //     } else if (command == 'B') { // Command to turn relay 2 OFF
// //       digitalWrite(RELAY2_PIN, HIGH); // Turn off relay 2
// //       Serial.println("Relay 2 OFF");
// //     } else if (command == 'C') { // Command to turn relay 3 ON
// //       digitalWrite(RELAY3_PIN, LOW); // Turn on relay 3
// //       Serial.println("Relay 3 ON");
// //     } else if (command == 'D') { // Command to turn relay 3 OFF
// //       digitalWrite(RELAY3_PIN, HIGH); // Turn off relay 3
// //       Serial.println("Relay 3 OFF");
// //     }
// //   }

// //   // Read temperature and humidity
// //   float humidity = dht.readHumidity();
// //   float tempC = dht.readTemperature();
// //   float tempF = dht.readTemperature(true);

// //   // Check if any reads failed and exit early (to try again).
// //   if (isnan(humidity) || isnan(tempC) || isnan(tempF)) {
// //     Serial.println("Failed to read from DHT sensor!");
// //     return;
// //   }

// //   // Print the readings to the Serial Monitor
// //   // Serial.print("Humidity: ");
// //   // Serial.print(humidity);
// //   // Serial.print(" %\t");
// //   // Serial.print("Temperature: ");
// //   // Serial.print(tempC);
// //   // Serial.print(" *C ");
// //   // Serial.print(tempF);
// //   // Serial.println(" *F");

// //   // Send data to serial for Arduino IoT Cloud
// //   Serial.print("humidity ");
// //   Serial.println(humidity);
// //   Serial.print("temperatureC ");
// //   Serial.println(tempC);
// //   Serial.print("temperatureF ");
// //   Serial.println(tempF);

// //   delay(2000); // Wait a few seconds between measurements
// // }