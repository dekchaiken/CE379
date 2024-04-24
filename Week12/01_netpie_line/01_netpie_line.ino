#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <DHT.h>
#define BAUD_RATE 115200

const char* ssid = "KenNoluv";
const char* password = "11111111";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "91590854-1aba-4b90-b3db-35e86a33eb72";
const char* mqtt_username = "HDaTRhsYkNrUcnzNBqQZt1qburco2jPU";
const char* mqtt_password = "5TQJpqJobcKk1ps4oqiBu5M1WQ4Rbnp5";

WiFiClient espClient;
PubSubClient client(espClient);

char msg[100];

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("connected");
    }
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

int ldr; // ประกาศตัวแปร ldr ชนิด int

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqtt_server, mqtt_port);
}

void loop() {
  String place = "ROOM 591";
    if (!client.connected()) {
    reconnect();
  }
    client.loop();
    int ldr = analogRead(A0);
    String data = "{\"data\": {\"ldr\": " + String(ldr) + "}}";
    Serial.println("ldr: " + data);
    client.publish("@shadow/data/update", data.c_str());
    delay(2000);
}
