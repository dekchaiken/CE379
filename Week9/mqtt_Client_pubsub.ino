#include <PubSubClient.h>
#include <ESP8266WiFi.h>


#define BAUD_RATE 115200
#include <DHT.h>
#define DHT_PIN_BUTTON D3
#define DHT_PIN D4

DHT dht(DHT_PIN, DHT11);


//Client1(publisher) --> TOPIC_A --> Client2 (Sub)
//Client2(publisher) --> TOPIC_B --> Client1 (Sub)
const char* ssid = "iPhone_win";
const char* password = "0863827465";
const char* mqttServer = "test.mosquitto.org";
const int mqttPort = 1883;
const char* Topic_A = "/dpu/cite/ce379/earn/a";
const char* Topic_B = "/dpu/cite/ce379/earn/b";

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) { // Subscribe add <-------------
   char* buffer = (char *) malloc(length + 1);
   memcpy(buffer, payload, length);
   buffer[length] = '\0';
   Serial.printf("Message received %s\n", buffer);
   float temp = dht.readTemperature();
   
   //String temp1 = String("Temperature: " + String(temp));
   if (strcmp(buffer, "Press") == 0 ) {
    client.publish(Topic_B,String(temp).c_str());
   }
   free(buffer);
} // <--------------------

void setup() {
  dht.begin();
  pinMode(DHT_PIN,LOW);
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWIFI Connected");
  Serial.print("IP Address : ");
  Serial.println(WiFi.localIP());

  //mqtt
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT.....");
    if (client.connect("cite:pawin")) {
      Serial.println("Connected to MQTT");
    } else {
      Serial.print("Failed with state: ");
      Serial.print(client.state());
      delay(2000);
    }
  }
  //Subscribe <------------------
  client.subscribe(Topic_A);

}
bool flag = false;
String press = "press";
void loop() {
  //Subsribe
  client.loop(); //<----------

  if (Serial.available() > 0) { //<--------------------Pubsub
    String str = Serial.readStringUntil('\n');
    Serial.printf("Sending : %s\n",str);
    client.publish(Topic_B,str.c_str());
  } //<----------------------------Pubsub

  if (digitalRead(DHT_PIN_BUTTON) == LOW && !flag) {
    flag = true;
  }else if (digitalRead(DHT_PIN_BUTTON) == HIGH && flag){
    client.publish(Topic_B,press.c_str());
    flag = false;

  }
}
