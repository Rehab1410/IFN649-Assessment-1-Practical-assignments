import paho.mqtt.publish as publish

# Replace with my EC2 instance's public IP address
broker_ip = "3.27.234.119"

# Publish a single message to the topic 'ifn649'
publish.single("ifn649", "Hello World", hostname=broker_ip)
print("message published")
