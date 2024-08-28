import serial
import csv
from datetime import datetime
import paho.mqtt.client as mqtt

# Open serial connection to HC-05
ser = serial.Serial('/dev/rfcomm0', 9600)

# MQTT setup
broker_address = "3.27.234.119"  # Replace with your EC2 instance's public IP
publish_topic = "sensor/data"
subscribe_topic = "command/control"
mqtt_client = mqtt.Client("RaspberryPiPublisher")

# Function to handle connection to MQTT broker
def on_connect(client, userdata, flags, rc):
    print("Connected to MQTT")
    print("Connection returned result: " + str(rc))
    client.subscribe(subscribe_topic)

# Function to handle received messages from MQTT broker
def on_message(client, userdata, msg):
    print("Received message: " + msg.topic + " -> " + msg.payload.decode())
    ser.write((msg.payload.decode() + '\n').encode()) # Send the received MQTT message directly over Bluetooth

mqtt_client.on_connect = on_connect
mqtt_client.on_message = on_message

# Connect to MQTT broker
mqtt_client.connect(broker_address, 1883, 60)

# Start MQTT loop
mqtt_client.loop_start()

# Open a CSV file to log data
with open('sensor_data.csv', 'a', newline='') as csvfile:
    csvwriter = csv.writer(csvfile)
    csvwriter.writerow(['Timestamp', 'Received Data'])

    try:
        while True:
            if ser.in_waiting > 0:  # Check if there is incoming data
                incoming_data = ser.readline().decode('utf-8').strip()  # Read and decode the data
                print("Received:", incoming_data)  # Print the received data
                csvwriter.writerow([datetime.now(), incoming_data])  # Log the data with a timestamp

                # Publish to MQTT broker
                mqtt_client.publish(publish_topic, incoming_data)
                print("Data published to MQTT broker")

                # Check soil moisture and send command to Teensy
                if "Soil Moisture Level" in incoming_data:
                    soil_moisture_value = int(incoming_data.split(":")[1].strip())
                    if soil_moisture_value < 30:  # Example threshold for dry soil
                        mqtt_client.publish(subscribe_topic, "BUZZER_ON")  # Publish to MQTT to control buzzer
                    else:
                        mqtt_client.publish(subscribe_topic, "BUZZER_OFF")  # Publish to MQTT to control buzzer

    except KeyboardInterrupt:
        print("Program interrupted by user.")
    except serial.SerialException as e:
        print(f"Serial exception: {e}")
    finally:
        ser.close()
        mqtt_client.loop_stop()
