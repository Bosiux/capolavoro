#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define MOISTURE A1


int light;

// DHT11: DATA-5V-GND FRONT-VIEW

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(MOISTURE,  INPUT);
  pinMode(DHTPIN,  INPUT);
  Serial.begin(9600);
  delay(500); 
  Serial.println("Avvio sistema");
  dht.begin();
}

void loop() {
  delay(500);

  int moistureValue = analogRead(MOISTURE);
  int moisturePercentage = map(moistureValue, 0, 1023, 0, 100);
  moisturePercentage = constrain(moisturePercentage, 0, 100);
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

 


  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" *C");
  Serial.print(" \t");
  Serial.print("Tstatus: ");
  Serial.println(moisturePercentage);
}
