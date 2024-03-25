#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#define BAUD_RATE 115200

#define BUTTON_PIN 4

#define RED_PIN 15
#define GREEN_PIN 12
#define BLUE_PIN 13
#define NUM_COLORS 3
#define RGB 3
#define MAX_CHAR_LEN 15
char COLORS_NAMES[NUM_COLORS][MAX_CHAR_LEN] = {"green", "yellow", "red"};
unsigned int COLORS[NUM_COLORS][RGB] = {
    {0, 1023, 0},
    {1023, 1023, 0},
    {1023, 0, 0},
    
};

const char *ssid = "sup.film";
const char *password = "dongkew28";
const char *mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char *Topic_A = "/dpu/cite/ce379/earn/a";
const char *Topic_B = "/dpu/cite/ce379/earn/b";

WiFiClient espClient;
PubSubClient client(espClient);

int state = 0;

void callback(char *topic, byte *payload, unsigned int length)
{
  char *buffer = (char *)malloc(length + 1); // สร้าง buffer ขนาดเท่ากับข้อมูลที่รับเข้ามา
  memcpy(buffer, payload, length);           // คัดลอกข้อมูลจาก payload ไปยัง buffer
  buffer[length] = '\0';                     // ตัวสุดท้ายของ buffer ต้องเป็น null เพื่อให้เป็น string
  Serial.printf("Message received: %s\n", buffer);

  // รับคำว่า Press จาก Buffer เข้ามาแล้วเปลี่ยนสีไฟโดยใช้การเปลี่ยน State ใช้ Switch case
  switch (state) {
    case 0:
      if (strcmp(buffer, "press") == 0){
          Serial.println(COLORS_NAMES[state]);
          // แสดงเขียว
          analogWrite(RED_PIN, 0);
          analogWrite(GREEN_PIN, COLORS[state][1]);
          analogWrite(BLUE_PIN, 0);
          state = 1;
      }
      delay(500);
      break;
    case 1:
      if (strcmp(buffer, "press") == 0) {
          Serial.println(COLORS_NAMES[state]);
          analogWrite(BLUE_PIN, 0);
          analogWrite(RED_PIN, COLORS[state][0]);
          analogWrite(GREEN_PIN, COLORS[state][1]);
          state = 2;
      }
      delay(500);
      break;
    case 2:
      if (strcmp(buffer, "press") == 0) {
          Serial.println(COLORS_NAMES[state]);
          analogWrite(RED_PIN, COLORS[state][0]);
          analogWrite(GREEN_PIN, 0);
          analogWrite(BLUE_PIN, 0);
          state = 3;
      }
      delay(500);
      break;
    default:
      state = 0;
      break;
  }
  free(buffer); // คืนหน่วยความจำที่ใช้ไป
}

void setup()
{
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.begin(BAUD_RATE);

  // WIFI
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println(".");
  }
  Serial.println("\nWIFI Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  // MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback); // เมื่อมีข้อมูลเข้ามาให้เรียกใช้ callback

  // Loop until we're reconnected
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("Cite:earn"))
    {
      Serial.println("Connected to MQTT");
    }
    else
    {
      Serial.print("Failed with state:");
      Serial.print(client.state());
      delay(2000);
    }
  }

  client.subscribe(Topic_B);
}

bool flag = false;

void loop()
{
  client.loop();
  // if (Serial.available() > 0)
  // {
  //   String str = Serial.readStringUntil('\n'); // รับค่าจาก Serial Monitor จนกว่าจะเจอ \n
  //   Serial.printf("Sending: %s\n", str);
  //   client.publish(Topic_A, str.c_str()); // c_str คือ แปลง String เป็น char array
  // }

  // กดปุ่มแล้วส่งคำว่า Press ไปให้ Topic_A
  if (digitalRead(BUTTON_PIN) == LOW && !flag)
  {
    flag = true;
  }
  else if (digitalRead(BUTTON_PIN) == HIGH && flag)
  {
    flag = false;
    Serial.println("Send : Press to Topic_A");
    client.publish(Topic_A, "Press");
  }
}
