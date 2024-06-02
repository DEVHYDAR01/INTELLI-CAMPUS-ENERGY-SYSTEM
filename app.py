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

# Arduino IoT Cloud settings
def logging_func():
    logging.basicConfig(
        datefmt="%H:%M:%S",
        format="%(asctime)s.%(msecs)03d %(message)s",
        level=logging.INFO,
    )

# Callback functions for relay states
def on_relay1_changed(client, value):
    if value:
        ser.write(b'O')
    else:
        ser.write(b'F')

def on_relay2_changed(client, value):
    if value:
        ser.write(b'A')
    else:
        ser.write(b'B')

def on_relay3_changed(client, value):
    if value:
        ser.write(b'C')
    else:
        ser.write(b'D')

# Function to read current and temperature values
def read_current_value(client=None):
    while ser.in_waiting:
        response = ser.readline().decode('utf-8').strip()
        if response.startswith("current1 "):
            current1 = float(response.split()[1])
            return current1
        elif response.startswith("current2 "):
            current2 = float(response.split()[1])
            return current2
        elif response.startswith("current3 "):
            current3 = float(response.split()[1])
            return current3
    return 0.0

def read_temp_humidity(client=None):
    while ser.in_waiting:
        response = ser.readline().decode('utf-8').strip()
        if response.startswith("humidity "):
            humidity = float(response.split()[1])
            return humidity
        elif response.startswith("temperatureC "):
            tempC = float(response.split()[1])
            return tempC
        elif response.startswith("temperatureF "):
            tempF = float(response.split()[1])
            return tempF
    return 0.0

if __name__ == "__main__":
    logging_func()
    client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY)

    client.register("relay1State", value=None, on_write=on_relay1_changed)
    client.register("relay2State", value=None, on_write=on_relay2_changed)
    client.register("relay3State", value=None, on_write=on_relay3_changed)
    client.register("current1", on_read=read_current_value, interval=10.0)
    client.register("current2", on_read=read_current_value, interval=10.0)
    client.register("current3", on_read=read_current_value, interval=10.0)
    client.register("humidity", on_read=read_temp_humidity, interval=10.0)
    client.register("temperatureC", on_read=read_temp_humidity, interval=10.0)
    client.register("temperatureF", on_read=read_temp_humidity, interval=10.0)

    client.start()

    try:
        while True:
            while ser.in_waiting:
                response = ser.readline().decode('utf-8').strip()
                print(response)
                if response.startswith("current1 "):
                    current1 = float(response.split()[1])
                    client["current1"] = current1
                elif response.startswith("current2 "):
                    current2 = float(response.split()[1])
                    client["current2"] = current2
                elif response.startswith("current3 "):
                    current3 = float(response.split()[1])
                    client["current3"] = current3
                elif response.startswith("humidity "):
                    humidity = float(response.split()[1])
                    client["humidity"] = humidity
                elif response.startswith("temperatureC "):
                    tempC = float(response.split()[1])
                    client["temperatureC"] = tempC
                elif response.startswith("temperatureF "):
                    tempF = float(response.split()[1])
                    client["temperatureF"] = tempF
            time.sleep(10)
    except KeyboardInterrupt:
        ser.close()
    except Exception as e:
        print(f"Exception: {e}")
        ser.close()












































# # Arduino IoT Cloud settings
# def logging_func():
#     logging.basicConfig(
#         datefmt="%H:%M:%S",
#         format="%(asctime)s.%(msecs)03d %(message)s",
#         level=logging.INFO,
#     )

# # Callback functions for relay states
# def on_relay1_changed(client, value):
#     if value:
#         ser.write(b'O')
#     else:
#         ser.write(b'F')

# def on_relay2_changed(client, value):
#     if value:
#         ser.write(b'A')
#     else:
#         ser.write(b'B')

# def on_relay3_changed(client, value):
#     if value:
#         ser.write(b'C')
#     else:
#         ser.write(b'D')

# # Function to read current value
# def read_current_value(client=None):
#     while ser.in_waiting:
#         response = ser.readline().decode('utf-8').strip()
#         if response.startswith("current "):
#             current = float(response.split()[1])
#             return current
#     return 0.0

# if __name__ == "__main__":
#     logging_func()
#     client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY)

#     client.register("relay1State", value=None, on_write=on_relay1_changed)
#     client.register("relay2State", value=None, on_write=on_relay2_changed)
#     client.register("relay3State", value=None, on_write=on_relay3_changed)
#     client.register("current", on_read=read_current_value, interval=10.0)

#     client.start()

#     try:
#         while True:
#             while ser.in_waiting:
#                 response = ser.readline().decode('utf-8').strip()
#                 print(response)
#                 if response.startswith("current "):
#                     current = float(response.split()[1])
#                     client["current"] = current
#             time.sleep(10)
#     except KeyboardInterrupt:
#         ser.close()
#     except Exception as e:
#         print(f"Exception: {e}")
#         ser.close()























# def logging_func():
#     logging.basicConfig(
#         datefmt="%H:%M:%S",
#         format="%(asctime)s.%(msecs)03d %(message)s",
#         level=logging.INFO,
#     )

# # Callback functions for relay states
# def on_relay1_changed(client, value):
#     if value:
#         ser.write(b'O')
#     else:
#         ser.write(b'F')

# def on_relay2_changed(client, value):
#     if value:
#         ser.write(b'A')
#     else:
#         ser.write(b'B')

# def on_relay3_changed(client, value):
#     if value:
#         ser.write(b'C')
#     else:
#         ser.write(b'D')

# if __name__ == "__main__":
#     logging_func()
#     client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY)

#     client.register("relay1State", value=None, on_write=on_relay1_changed)
#     client.register("relay2State", value=None, on_write=on_relay2_changed)
#     client.register("relay3State", value=None, on_write=on_relay3_changed)
#     client.register("current")

#     client.start()

#     try:
#         while True:
#             while ser.in_waiting:
#                 response = ser.readline().decode('utf-8').strip()
#                 print(response)
#                 if response.startswith("current "):
#                     current = float(response.split()[1])
#                     client["current"] = current
#             time.sleep(10)
#     except KeyboardInterrupt:
#         ser.close()
#     except Exception as e:
#         print(f"Exception: {e}")
#         ser.close()































# def logging_func():
#     logging.basicConfig(
#         datefmt="%H:%M:%S",
#         format="%(asctime)s.%(msecs)03d %(message)s",
#         level=logging.INFO,
#     )

# # Callback functions for relay states
# def on_relay1_changed(client, value):
#     if value:
#         ser.write(b'O')
#     else:
#         ser.write(b'F')

# def on_relay2_changed(client, value):
#     if value:
#         ser.write(b'A')
#     else:
#         ser.write(b'B')

# def on_relay3_changed(client, value):
#     if value:
#         ser.write(b'C')
#     else:
#         ser.write(b'D')

# if __name__ == "__main__":
#     logging_func()
#     client = ArduinoCloudClient(device_id=DEVICE_ID, username=DEVICE_ID, password=SECRET_KEY)

#     client.register("relay1State", value=None, on_write=on_relay1_changed)
#     client.register("relay2State", value=None, on_write=on_relay2_changed)
#     client.register("relay3State", value=None, on_write=on_relay3_changed)
#     client.register("humidity")
#     client.register("temperatureC")
#     client.register("temperatureF")

#     client.start()

#     try:
#         while True:
#             while ser.in_waiting:
#                 response = ser.readline().decode('utf-8').strip()
#                 print(response)
#                 if response.startswith("humidity "):
#                     humidity = float(response.split()[1])
#                     client["humidity"] = humidity
#                 elif response.startswith("temperatureC "):
#                     tempC = float(response.split()[1])
#                     client["temperatureC"] = tempC
#                 elif response.startswith("temperatureF "):
#                     tempF = float(response.split()[1])
#                     client["temperatureF"] = tempF
#             time.sleep(10)
#     except KeyboardInterrupt:
#         ser.close()
#     except Exception as e:
#         print(f"Exception: {e}")
#         ser.close()