#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <DHT.h>

#define BAUD_RATE 115200
#define WS_PORT 81
#define DHT_PIN D4

const char* ssid = "KenNoluv";
const char* password = "11111111";

WebSocketsServer webSocket = WebSocketsServer(WS_PORT);
DHT dht(DHT_PIN, DHT11);

void setup() {
  dht.begin();
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
  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  switch (type) {
    case WStype_TEXT:
      handleWebSocketText(num, payload, length);
      break;
    case WStype_CONNECTED: {
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connection from %d.%d.%d.%d\n", num, ip[0], ip[1], ip[2], ip[3]);
      webSocket.sendTXT(num, "Hello from 8266");
    }
    break;
    case WStype_DISCONNECTED:
      Serial.printf("[%u] Disconnected\n", num);
      break;
  }
}

void handleWebSocketText(uint8_t num, uint8_t * payload, size_t length) {
  String command = String((char*)payload);
  float sensorValue = 0.0;
  
  if (command.equalsIgnoreCase("t")) {
    sensorValue = dht.readTemperature();
  } else if (command.equalsIgnoreCase("h")) {
    sensorValue = dht.readHumidity();
  }

  String sensorData = "Sensor Value: " + String(sensorValue);
  webSocket.sendTXT(num, sensorData);
}

void loop() {
  webSocket.loop();
}
