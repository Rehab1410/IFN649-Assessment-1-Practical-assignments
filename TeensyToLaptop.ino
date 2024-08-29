#include <DHT.h> // Include the DHT library

// Pin Definitions
const int soilPin = 20;    // Soil moisture sensor connected to analog pin A0
const int dhtPin = 21;      // DHT-11 sensor connected to digital pin 2
const int buzzerPin = 17;  // Buzzer connected to digital pin 17

// Initialize DHT sensor
#define DHTTYPE DHT11     // Define the type of DHT sensor
DHT dht(dhtPin, DHTTYPE);  // Create a DHT object

void setup() {
  pinMode(buzzerPin, OUTPUT); // Set buzzer pin as output
  Serial.begin(9600);         // Start serial communication
  dht.begin();                // Initialize DHT sensor
}

void loop() {
  // Read soil moisture sensor
  int soilMoistureValue = analogRead(soilPin);
  Serial.print("Soil Moisture Level: ");
  Serial.println(soilMoistureValue);

  // Read DHT-11 sensor
  float humidity = dht.readHumidity();       // Read humidity
  float temperature = dht.readTemperature(); // Read temperature

  // Check if any reads failed and exit early (to try again).
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" *C");
  }

  // Control buzzer based on soil moisture value
  if (soilMoistureValue < 30) { // Example threshold for dry soil
    digitalWrite(buzzerPin, HIGH); // Turn the buzzer on
    delay(500); // Buzzer on for 0.5 second
    digitalWrite(buzzerPin, LOW);  // Turn the buzzer off
    delay(500); // Buzzer off for 0.5 second
  } else {
    digitalWrite(buzzerPin, LOW);  // Keep the buzzer off if soil moisture is sufficient
    delay(2000); // Wait for two seconds before the next reading
  }
}
