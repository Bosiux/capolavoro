
/*

    Esempi usati:
        ESP8266 -> WifiClient
        ESP8266HTTPClient -> PostHttpClient

*/

#include <ESP8266WiFi.h>


#ifndef STASSID
#define STASSID "#########"
#define STAPSK "#########"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

// Server 
const char* host = "135.125.132.97";
const uint16_t port = 5000;


const int analogPin = A0;  

void setup() {
  Serial.begin(115200);

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
}

void loop() {
  
  if (Serial.available() > 0) {

  String data = Serial.readStringUntil('\n');
  Serial.println("Received: " + data);
  
  int tempIndex = data.indexOf("T:") + 2;
  int humidityIndex = data.indexOf(",H:") + 3;
  
  String temperature = data.substring(tempIndex, data.indexOf(',', tempIndex));
  String humidity = data.substring(humidityIndex);
    
  String data = "value=" + String(temperature) + String(humidity);

  Serial.print("Connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("Connection failed");
    delay(10000); 
    return;
  }

  Serial.println("Sending data to server");
  if (client.connected()) {
    client.print("GET /update?");
    client.print(data);
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(host);
    client.println("Connection: close");
    client.println();
  }

  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(10000); 
      return;
    }
  }

  Serial.println("Receiving from remote server");
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }


  Serial.println();
  Serial.println("Closing connection");
  client.stop();

  delay(10000);
  }  
}