#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <DHT.h>

#define BAUD_RATE 115200
#define WS_PORT 81
#define LED_PIN 2

const char* ssid = "Nickie";
const char* password = "23252325";

WebSocketsServer webSocket = WebSocketsServer(WS_PORT);

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
  pinMode(LED_PIN, OUTPUT);
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      Serial.printf("[%u] Text: %s\n", num, payload);
      if (strcmp((char*)payload, "on") == 0) {
        digitalWrite(LED_PIN, LOW); // Turn LED on
      } else if (strcmp((char*)payload, "off") == 0) {
        digitalWrite(LED_PIN, HIGH); // Turn LED off
      }
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connection from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      webSocket.sendTXT(num, "Hello from 8266 WebSocket Server");
    }
    break;
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected\n", num);
      break;
  }
}

void loop() {
  webSocket.loop();
}