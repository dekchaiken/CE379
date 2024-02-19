#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>

#define BAUD_RATE 115200
#define WS_PORT 81
#define LED_PIN 2  //1

const char* ssid = "Top";       //ชื่อของ WiFi
const char* password = "top54811";   //รหัสผ่านของ WiFi

WebSocketsServer webSocket = WebSocketsServer(WS_PORT);  //ชนิด - ชื่อตัวแปร - Opject [1-2-3] //1
int number;

void setup() {
  pinMode(LED_PIN, OUTPUT);  //2
  digitalWrite(LED_PIN, HIGH); //3
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

void webSocketEvent(uint8_t num, WStype_t type, uint8 * payload, size_t length) {    
  switch (type) {
  case WStype_TEXT:
    Serial.printf("[%u] Text: %s\n", num, payload);
    number = atoi((char *)payload);
    for (int i = 0; i < number; i++) {
        digitalWrite(LED_PIN, LOW); // Turn LED on
        delay(500); // Wait for 500 milliseconds
        digitalWrite(LED_PIN, HIGH); // Turn LED off
        delay(500); // Wait for 500 milliseconds
      }
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

void loop() {
  webSocket.loop(); 
}
