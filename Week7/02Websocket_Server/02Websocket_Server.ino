#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

#define BAUD_RATE 115200
#define WS_PORT 81
#define LED_PIN 2
#define BUTTON_PIN 4

#define RED_PIN 15
#define GREEN_PIN 12
#define BLUE_PIN 13

const char* ssid = "Kuyken";
const char* password = "123456789";

WebSocketsServer webSocket = WebSocketsServer(WS_PORT);

int buttonState; // Declare buttonState variable globally

void setup() {
  Serial.begin(BAUD_RATE);
  delay(10);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

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
      if (strcmp((char*)payload, "red") == 0) {
        analogWrite(RED_PIN, 1023);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 0);
      } else if (strcmp((char*)payload, "green") == 0) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 1023);
        analogWrite(BLUE_PIN, 0);
      } else if (strcmp((char*)payload, "blue") == 0) {
        analogWrite(RED_PIN, 0);
        analogWrite(GREEN_PIN, 0);
        analogWrite(BLUE_PIN, 1023);
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
  buttonState = digitalRead(BUTTON_PIN); // Read button state

  if (buttonState == LOW) {
    Serial.printf("Sendtxt");
    webSocket.broadcastTXT("get_temperature"); // Send to all connected clients
  }
  delay(10); // Add a small delay
}
