#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define BAUD_RATE 115200
#define HTTP_PORT 80
const char* ssid = "KenNoluv";
const char* password = "11111111";

ESP8266WebServer server(HTTP_PORT);

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

    server.on("/", [](){
        server.send(200, "text/plain", "Hello, from ESP8266 Webserver!");
    });
    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    server.handleClient();
}