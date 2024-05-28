#!/usr/bin/env python3
import time
import logging

import serial
from arduino_iot_cloud import ArduinoCloudClient

# Set up serial communication
ser = serial.Serial('/dev/ttyACM0', 9600)  # Adjust port as needed
time.sleep(2)  # Wait for the serial connection to initialize

# Arduino IoT Cloud settings
DEVICE_ID = b"fdfcaea5-5bf1-4901-a8b7-40166c687ff9"
SECRET_KEY = b"d!C1d3C65J9O7uuhwWMdpfat#"

def logging_func():
    logging.basicConfig(
        datefmt="%H:%M:%S",
        format="%(asctime)s.%(msecs)03d %(message)s",
        level=logging.INFO,
    )

# This function is executed each time the "relayState" variable changes
def on_relay_changed(client, value):
    if value:
        ser.write(b'O')  # Turn relay on
    else:
        ser.write(b'F')  # Turn relay off

if __name__ == "__main__":
    logging_func()
    client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY)

    client.register("current")  
    client.register("relayState", value=None, on_write=on_relay_changed)
    
    client.start()

    try:
        while True:
            ser.write(b'C')  # Send command to read current
            response = ser.readline().decode('utf-8').strip()
            print(response)
            if "Current:" in response:
                current_value = float(response.split()[1])
                client["current"] = current_value
            time.sleep(10)
    except KeyboardInterrupt:
        ser.close()
    except Exception as e:
        print(f"Exception: {e}")
        ser.close()
