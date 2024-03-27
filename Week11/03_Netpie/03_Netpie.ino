#include <ESP8266WiFi.h>
#include <PubSubClient.h>

#include <DHT.h>
#define BAUD_RATE 115200
#define DHT_PIN D4

const char* ssid = "KenNoluv";
const char* password = "11111111";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "f33eba60-3673-4ea0-ba7b-f823d62802c6";
const char* mqtt_username = "HqJU484nVJ7D23zebfKr9wAAyZvLeMe7";
const char* mqtt_password = "VtsXNLyBGM7qPWJomMZFusPzxRPSDgNN";

WiFiClient espClient;
PubSubClient client(espClient);
DHT dht(DHT_PIN, DHT11);

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

void setup() {
  dht.begin();
  pinMode(DHT_PIN,LOW);
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
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();
  String place = "ROOM 591";
    if (!client.connected()) {
    reconnect();
  }
  client.loop();
  String data = "{\"data\": {\"humidity\":" + String(humidity) + ", \"temperature\":" + String(temperature) + ", \"place\": \"" +  String(place) + "\"}}";
  Serial.println(data);
  // data.toCharArray(msg, (data.length() + 1));
  client.publish("@shadow/data/update", data.c_str());
  delay(2000);
}
