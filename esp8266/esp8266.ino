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
