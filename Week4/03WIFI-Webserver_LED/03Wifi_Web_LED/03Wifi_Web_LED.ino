#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define BAUD_RATE 115200
#define HTTP_PORT 80
const char* ssid = "KenNoluv";
const char* password = "11111111";

ESP8266WebServer server(HTTP_PORT);

void handleRoot() {
    String html = "<!DOCTYPE html>\n";
    html += "<html lang=\"en\">\n";
    html += "<head>\n";
    html += "<meta charset=\"UTF-8\">\n";
    html += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
    html += "<title>LED Control</title>\n";
    html += "</head>\n";
    html += "<body>\n";
    html += "<h1>LED Control</h1>\n";
    html += "<form action=\"/led\" method=\"post\">\n";
    html += "<input type=\"submit\" name=\"state\" value=\"ON\">\n";
    html += "<input type=\"submit\" name=\"state\" value=\"OFF\">\n";
    html += "</form>\n";
    html += "</body>\n";
    html += "</html>\n";
    server.send(200, "text/html", html);
}
  

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
    server.on("/", handleRoot);
    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    server.handleClient();
}