#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "KenNoluv";
const char* password = "11111111";
const char* mqtt_server = "broker.netpie.io";
const int mqtt_port = 1883;
const char* mqtt_Client = "91590854-1aba-4b90-b3db-35e86a33eb72";
const char* mqtt_username = "HDaTRhsYkNrUcnzNBqQZt1qburco2jPU";
const char* mqtt_password = "5TQJpqJobcKk1ps4oqiBu5M1WQ4Rbnp5";

const char* topic_sub = "@msg/test/in";  // Topic to subscribe for receiving messages
const char* topic_pub = "@msg/test/out"; // Topic to publish messages to be sent to the Serial monitor

WiFiClient espClient;
PubSubClient client(espClient);

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection…");
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      Serial.println("NETPIE2020 connected");
      client.subscribe(topic_sub); // Subscribe to the incoming message topic
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("try again in 5 seconds");
      delay(5000);
    }
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Check if the received message is on the subscribed topic
  if (strcmp(topic, topic_sub) == 0) {
    Serial.print("Message arrived [");
    Serial.print(topic);
    Serial.print("] ");
    String message;
    for (int i = 0; i < length; i++) {
      message = message + (char)payload[i];
    }
    Serial.println(message);
  }
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting...");
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
  client.setCallback(callback);
  client.publish(topic_pub, "Hello from NETPIE2020");  // Initial message on outgoing topic
  Serial.println("Message Published");
}

void loop() {
  if (!client.connected()) {
    delay(5000); // Prevent blocking on errors
    reconnect();
  }
  client.loop();

  if (Serial.available() > 0) {
    String str = Serial.readStringUntil('\n');
    Serial.printf("Sending to MQTT: %s\n", str.c_str());
    client.publish(topic_pub, str.c_str());
  }
}
