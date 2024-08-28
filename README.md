# IFN649-Assessment-1-Practical-assignments

# IoT Network Project: Sensor Data Collection and Actuator Control

## Overview

This project demonstrates an IoT network setup using a Teensy microcontroller, Raspberry Pi, and AWS MQTT broker. The system collects sensor data from soil moisture and DHT-11 sensors, transmits the data to a Raspberry Pi via Bluetooth, and publishes the data to an AWS MQTT broker. The system also receives commands from the AWS MQTT broker to control a buzzer connected to the Teensy.

## Hardware Configuration

- **Teensy Microcontroller**: Connected to a soil moisture sensor, DHT-11 sensor, and a buzzer.
- **Raspberry Pi**: Receives data from the Teensy via Bluetooth and interfaces with the AWS MQTT broker.
- **AWS EC2 Instance**: Hosts the MQTT broker (Mosquitto) for communication between devices.

## Software Setup

### 1. Teensy Code

The Teensy microcontroller collects data from the sensors and sends it to the Raspberry Pi via Bluetooth. It also listens for commands from the Raspberry Pi to control the buzzer.

### 2. Raspberry Pi Code

- **`receive_data2.py`**: This single script performs multiple functions:
  - Receives sensor data from the Teensy via Bluetooth.
  - Logs the sensor data into `sensor_data.csv`.
  - Publishes the sensor data to the AWS MQTT broker.
  - Subscribes to an MQTT topic to receive commands and forwards these commands to the Teensy via Bluetooth to control the buzzer.
- **`publish_data2.py`**: Publishes messages to the MQTT topic.


### 3. AWS MQTT Broker

An MQTT broker is set up on an AWS EC2 instance using Mosquitto to facilitate communication between the Raspberry Pi and the Teensy.

## Files in the Repository

- **`ssessment1-IFN649.ino`**: Arduino code for the Teensy microcontroller to handle sensor data collection and actuator control.
- **`receive_data2.py`**: Merged Python script for the Raspberry Pi to handle data reception, logging, MQTT publishing, and command forwarding.
- **`sensor_data.csv`**: CSV file where sensor data is logged. This file is automatically created by `receive_data2.py` when data is received from the Teensy.
- **`publish_data2.py`**: Publishes messages to the MQTT topic.


## How to Run the Project

1. **Set Up the Hardware**: Connect the sensors and buzzer to the Teensy and ensure the Bluetooth module is paired with the Raspberry Pi.
2. **Upload the Teensy Code**: Use the Arduino IDE to upload `ssessment1-IFN649.ino` to the Teensy microcontroller.
3. **Run the Raspberry Pi Script**:
   - Execute `receive_data2.py` on the Raspberry Pi to start receiving data, publishing to MQTT, and handling commands.
4. **Monitor MQTT Broker**: Use Mosquitto tools or any MQTT client to monitor the messages being published and received.

## Demonstration Results

- Successfully collected and transmitted sensor data from the Teensy to the Raspberry Pi.
- Data successfully logged in `sensor_data.csv`.
- Data successfully published to AWS MQTT broker.
- Commands from the MQTT broker successfully controlled the buzzer on the Teensy.

## License

This project is licensed under the MIT License.
