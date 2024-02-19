#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define BAUD_RATE 115200
#define HTTP_PORT 80
#define LED_PIN 2

const char* ssid = "KenNoluv";      //ชื่อของ WiFi
const char* password = "11111111";  //รหัสผ่านของ WiFi

ESP8266WebServer server(HTTP_PORT);     //สร้างอ็อบเจ็กต์ของคลาส ESP8266WebServer โดยกำหนดพอร์ตที่ใช้เป็น 80

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

    for (int i = 1; i <= 6; i++) {      //สร้างลูป for เพื่อสร้างปุ่มสำหรับส่งค่าไปที่เว็บเซิร์ฟเวอร์
        html += "<form action=\"/led\" method=\"post\">\n";
        html += "<input type=\"hidden\" name=\"value\" value=\"" + String(i) + "\">\n";
        html += "<input type=\"submit\" value=\"" + String(i) + "\">\n";
        html += "</form>\n";
    }

    html += "</body>\n";
    html += "</html>\n";
    server.send(200, "text/html", html);    //ส่งหน้าเว็บไซต์กลับไปที่เบราว์เซอร์
}

void handleLED() {
    String value = server.arg("value");     //ดึงค่าข้อ arg ที่ชื่อ value มาเก็บไว้ในตัวแปร value

    
    int flashCount = value.toInt();
    if (flashCount >= 1 && flashCount <= 6) {
        
        for (int i = 0; i < flashCount; i++) {
            digitalWrite(LED_PIN, LOW);
            delay(500);  
            digitalWrite(LED_PIN, HIGH);
            delay(500);
        }
    }

    server.sendHeader("Location", "/");   //ส่งหัวข้อ Location กลับไปที่หน้าเว็บไซต์
    server.send(303);       //ส่งสถานะ 303 กลับไปที่หน้าเว็บไซต์
}

void setup() {
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH);    // กำหนดให้ขา D2 มีสถานะเป็น LOW
    Serial.begin(BAUD_RATE);
    delay(10);
    Serial.println('\n');
    Serial.println("Connecting to WiFi");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {     //รอจนกว่าจะเชื่อมต่อกับ WiFi สำเร็จ
        delay(500);
        Serial.print(".");
    }
    Serial.println('\n');
    Serial.println("Connected to WiFi");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.on("/", handleRoot);
    server.on("/led", HTTP_POST, handleLED);    //กำหนดให้เมื่อมีการส่งข้อมูลเข้ามาที่ /led จะเรียกใช้ฟังก์ชัน handleLED

    server.begin();
    Serial.println("HTTP server started");  //แสดงข้อความว่าเริ่มต้นเซิร์ฟเวอร์ HTTP แล้ว
}

void loop() {
    server.handleClient();  //รอรับคำร้องขอจากเบราว์เซอร์
}
