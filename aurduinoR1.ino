#include <DHT.h>

#define DHTPIN A1 // analog pin A1
#define MOISTURE_SENSOR_PIN A0
#define DHTTYPE DHT11

// DHT11: DATA-5V-GND FRONT-VIEW
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  delay(1000); 
  Serial.println("Avvio sistema");
  dht.begin();
}

void loop() {
  delay(1500);
  int sensorValue = analogRead(MOISTURE_SENSOR_PIN);
  float moidtureHumidity = map(sensorValue, 0, 1023, 0, 100);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (temperature > 20) {
    digitalWrite(5, HIGH);
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" *C");
  Serial.print("Soil Humidity: ");
  Serial.print(moidtureHumidity);
  Serial.println(" %");

  // Send temperature and humidity to ESP8266
  Serial.print("T:");
  Serial.print(temperature);
  Serial.print(",H:");
  Serial.println(humidity);
}
