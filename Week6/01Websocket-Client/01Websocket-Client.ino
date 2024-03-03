#include <ESP8266WiFi.h>
#include <WebSocketsClient.h> // Note the corrected library name

#define BAUD_RATE 115200
#define WS_PORT 81


const char* ssid = "Kuyken";
const char* password = "123456789";
const char* server = "192.168.137.60";

WebSocketsClient webSocket; // Note the corrected library name

void setup() {
  Serial.begin(BAUD_RATE);
  delay(10);
  Serial.println('\n');
  Serial.println("Connecting to WiFi");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  webSocket.begin(server, WS_PORT);
  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      break;
    case WStype_CONNECTED: {
      webSocket.sendTXT("Hello from ESP8266 WebSocket Client");
    }
    break;
    case WStype_DISCONNECTED:
      Serial.println("Disconnected");
      break;
  }
}

void loop() {
  webSocket.loop();
  if(Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    if (command == "red" || command == "blue" || command == "green") {
      webSocket.sendTXT(command);
      Serial.println("Command Sent: " + command);
    } else {
      Serial.println("Invalid Command. Usage: 'red' or 'blue' or 'green'.");
    }
  }
}
