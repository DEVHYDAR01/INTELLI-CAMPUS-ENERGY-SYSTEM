# IntelliCampus Energy System

## Overview

The IntelliCampus Energy System is an innovative IoT-based solution designed to enhance energy management within university buildings. By integrating real-time monitoring and control capabilities, the system aims to optimize energy consumption, reduce costs, and promote sustainability.

## Features

- **Real-Time Monitoring**: Utilizes various sensors to monitor current, temperature, humidity, motion, and light levels.
- **Energy Optimization**: Automatically controls appliances based on sensor data to optimize energy usage.
- **Remote Control**: Provides a user-friendly dashboard through the Arduino IoT Cloud for remote monitoring and control.
- **Auto Mode**: Automatically manages lighting based on occupancy and ambient light levels.
- **Manual Control**: Allows users to manually control appliances via the cloud interface.

## Components

### Hardware

- **Raspberry Pi**: Acts as the main control unit and handles cloud communication.
- **Arduino Microcontrollers**: Interfaces with sensors and relays for local data processing and control.
- **Sensors**:
  - ACS712 Current Sensor
  - DHT11 Temperature and Humidity Sensor
  - Motion Sensor
  - Light Sensor
- **Relays**: Controls power to various loads (e.g., light bulbs, sockets, fans).

### Software

- **Arduino Sketch**: Manages sensor readings and relay control.
- **Python Script**: Handles cloud communication, data processing, and control logic on the Raspberry Pi.

## Installation and Setup

### Hardware Setup

1. **Connect Sensors and Relays**:
   - Connect the ACS712 current sensors to A3, A4, and A5 pins on the Arduino.
   - Connect the DHT11 sensor to pin 2 on the Arduino.
   - Connect the motion sensor to an appropriate GPIO pin.
   - Connect the light sensor to an appropriate GPIO pin.
   - Connect relays to control the loads.

2. **Connect Arduino to Raspberry Pi**:
   - Use a USB cable to connect the Arduino to the Raspberry Pi.

### Software Setup

1. **Arduino Code**:
   - Upload the provided Arduino sketch to the Arduino board.
   - Ensure the sketch includes the necessary libraries and pin configurations.

2. **Python Environment**:
   - Install Python 3.x on the Raspberry Pi.
   - Install required libraries using pip:
     ```bash
     pip install arduino-iot-cloud swig serial
     ```

3. **Arduino Cloud Setup**:
   - Create an Arduino Cloud account.
   - Set up a new device and thing in the Arduino Cloud.
   - Create and configure cloud variables (e.g., relay states, current readings).

4. **Python Script**:
   - Update the `credentials.py` file with your Arduino Cloud device ID and secret key.
   - Run the Python script on the Raspberry Pi:
     ```bash
     python app.py
     ```

## Usage

- **Auto Mode**: 
  - When enabled, the system automatically manages the lighting based on motion detection and light levels.
- **Manual Control**:
  - Use the Arduino Cloud dashboard to manually turn on/off appliances.

## Contribution

We welcome contributions to improve the IntelliCampus Energy System. Feel free to fork the repository, make changes, and submit pull requests.

## License

This project is licensed under the MIT License. See the LICENSE file for details.

## Acknowledgements

We would like to thank our supervisors and mentors for their guidance and support throughout this project. Special thanks to the Arduino community for their invaluable resources and support.

---

