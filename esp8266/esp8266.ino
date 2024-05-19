#include <ESP8266WiFi.h>

const char* ssid = "##########";         // Replace with your network SSID
const char* password = "##########"; // Replace with your network password
const char* host = "dbosio.space";      // Server hostname
const int port = 5000;                  // Server port

WiFiClient client;

void setup() {
  Serial.begin(9600); // Start serial communication at 9600 baud rate
  
  // Connect to Wi-Fi network
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
  if (Serial.available()) { // Check if data is available to read
    String data = Serial.readStringUntil('\n'); // Read the incoming data until a newline character is received
    Serial.print("Received data: "); // Optionally, print the received data to its own serial monitor
    Serial.println(data);
    
    if (!client.connect(host, port)) {
      Serial.println("Connection to server failed");
      return;
    }

    // Send the data to the server
    client.print(data);

    // Wait for the server's response (optional)
    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
        break;
      }
    }

    // Close the connection
    client.stop();
  }
}
