#include <DHT.h> // Include the DHT library

// Pin Definitions
const int soilPin = 20;    // Soil moisture sensor connected to analog pin A0
const int dhtPin = 21;     // DHT-11 sensor connected to digital pin 2
const int buzzerPin = 17;  // Buzzer connected to digital pin 17

// Initialize DHT sensor
#define DHTTYPE DHT11     // Define the type of DHT sensor
DHT dht(dhtPin, DHTTYPE);  // Create a DHT object

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  Serial1.begin(9600);        // Start serial communication over Serial1 for HC-05
  dht.begin();                // Initialize DHT sensor
}

void loop() {
  // Read soil moisture sensor
  int soilMoistureValue = analogRead(soilPin);
  Serial1.print("Soil Moisture Level: "); // Use Serial1 for Bluetooth communication
  Serial1.println(soilMoistureValue);

  // Read DHT-11 sensor
  float humidity = dht.readHumidity();       // Read humidity
  float temperature = dht.readTemperature(); // Read temperature

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial1.println("Failed to read from DHT sensor!"); // Use Serial1 for Bluetooth communication
  } else {
    Serial1.print("Humidity: ");
    Serial1.print(humidity);
    Serial1.print(" %\t");
    Serial1.print("Temperature: ");
    Serial1.print(temperature);
    Serial1.println(" *C");
  }

  // Check for commands from Raspberry Pi
  if (Serial1.available() > 0) {
    String command = Serial1.readStringUntil('\n');
command.trim();  // Remove any leading/trailing whitespace

if (command == "BUZZER_ON") {
    digitalWrite(buzzerPin, HIGH);  // Turn the buzzer on
} else if (command == "BUZZER_OFF") {
    digitalWrite(buzzerPin, LOW);   // Turn the buzzer off
}
  }

  delay(2000); // Wait for two seconds before the next reading
}