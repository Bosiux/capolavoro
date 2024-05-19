# Capolavoro 2023/2024

# Indice
1. [Schema](#Schema)
2. [Codice](#Codice)
3. [Realizzazione](#Realizzazione)
4. [Montaggio](#Montaggio)
5. [Server](#Server)

   
# Schema
![image](./resources/tinkercad_scheme.png)





# Codice

### aurduinoR1.ino [link](./aurduinoR1/aurduinoR1.ino)
```
#include <DHT.h>

#define DHTPIN A0
#define DHTTYPE DHT11
#define MOISTURE A1
int light;

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


```


### esp8266.ino [link](./esp8266/esp8266.ino)

```
#include <ESP8266WiFi.h>

const char* ssid = "##########";         // Replace with your network SSID
const char* password = "##########"; // Replace with your network password
const char* host = "dbosio.space";      // Server hostname
const int port = 5000;                  // Server port
WiFiClient client;

void setup() {
  Serial.begin(9600); 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (Serial.available()) {
    String data = Serial.readStringUntil('\n');
    Serial.print("Received data: "); 
    Serial.println(data);
    
    if (!client.connect(host, port)) {
      Serial.println("Connection to server failed");
      return;
    }

    client.print(data);
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        break;
      }
    }
    client.stop();
  }
}

```

# Realizzazione
### Per il processo di realizzazione del pezzo mi sono rivolto all'azienda [Alberici Stampi](https://www.albericistampi.it)
![](./resources/realizzazione-1.jpg)
![](./resources/realizzazione-2.jpg)
![](./resources/realizzazione-3.jpg)

# Montaggio
### Per il processo di montaggio si è cercato di seguire lo [schema elettrico](#Schema)

![](./resources/montaggio-1.jpg)
![](./resources/montaggio-2.jpg)
![](./resources/cablagio.jpg)


### Per stabilizzare la tensione fornita dai pannelli solari a 5v è stato necessario l'utilizzo di uno stabilizzatore di tensione posizionato sul lato del pezzo, il tutto al fine di non danneggiare i sensori e componenti.
### Il codice per entrambi i micro-controllori è stato caricato singolarmente per poi alimentare il tutto con una pila 9v


# Server
Lo script [server.py](./server/server.py) si occupa di ricevere le informazioni, dividerle e salvarle in un file data.csv.
Npm si occupa invece di hostare un sito web, quest'ultimo utilizza [chart.js](https://www.chartjs.org) per mostrare i dati salvati escludendo gli errori di registrazione.



[vai all'indice](#Indice)
