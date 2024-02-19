#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define BAUD_RATE 115200
#define HTTP_PORT 80
#define LED_PIN 2

const char* ssid = "KenNoluv";       //ชื่อของ WiFi
const char* password = "11111111";   //รหัสผ่านของ WiFi

ESP8266WebServer server(HTTP_PORT);

void handleRoot() {   //สร้างฟังก์ชัน handleRoot ที่ใช้สำหรับสร้างหน้าเว็บไซต์
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

void handleLED() {
    String state = server.arg("state");  //ดึงค่าข้อ arg ที่ชื่อ state มาเก็บไว้ในตัวแปร state
    if (state == "ON")
        digitalWrite(LED_PIN, LOW);
    else
        digitalWrite(LED_PIN, HIGH);
    server.sendHeader("Location", "/");  //ส่งหัวข้อ Location กลับไปที่หน้าเว็บไซต์
    server.send(303);                   //ส่งสถานะ 303 กลับไปที่หน้าเว็บไซต์
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH);    // กำหนดให้ขา D2 มีสถานะเป็น LOW
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
    server.on("/led", HTTP_POST, handleLED);

    server.begin();
    Serial.println("HTTP server started");
}

void loop(){
    server.handleClient();
}