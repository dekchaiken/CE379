#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#define BAUD_RATE 115200
WiFiClient espClient;
PubSubClient client(espClient);
#define BUTTON_PIN 4
#define LED_PIN 2
#define RED_PIN 15
#define GREEN_PIN 12
#define BLUE_PIN 13
#define NUM_COLORS 5
#define MAX_CHAR_LEN 15
#define RGB 5
bool ledStatus = false;
const char* ssid = "KenNoluv";
const char* password = "11111111";
const char* CLIENT_ID = "91590854-1aba-4b90-b3db-35e86a33eb72";
const char* TOKEN = "HDaTRhsYkNrUcnzNBqQZt1qburco2jPU";
const char* SECRET = "5TQJpqJobcKk1ps4oqiBu5M1WQ4Rbnp5";
const char* mqttServer = "broker.netpie.io";
const int mqttPort = 1883;

const char* TOPIC = "@shadow/data/update";
const char* TOPIC2 = "@msg/test1";
float temp;
float ht;
const char* Sub_TOPIC = "@msg/led";
char COLOR_NAMES[NUM_COLORS][MAX_CHAR_LEN] = { "red","green", "blue"};
unsigned int COLORS[NUM_COLORS][RGB] = {
  { 1024, 0, 0 },
  { 0, 1024, 0 },
  { 0, 0, 1024 }

};

bool redStatus = false;
bool GreenStatus = false;
bool BlueStatus = false;
int state = 0;
void setup() {
  // put your setup code here, to run once:
   pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
   pinMode(BUTTON_PIN, INPUT);
  Serial.begin(BAUD_RATE);
  WiFi.begin(ssid, password);
  pinMode(LED_PIN,OUTPUT);
  digitalWrite(LED_PIN,HIGH);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    
    Serial.println("รอ..............");
    digitalWrite(LED_PIN,LOW);
    digitalWrite(LED_PIN,HIGH);
  }
  client.setCallback(callback);
  Serial.println("\nWiFi connected");
  Serial.print("IP Addrees: ");
  Serial.println(WiFi.localIP());
  client.setServer(mqttServer,mqttPort);
  client.setCallback(callback);
  while(!client.connected()){
     Serial.println("Connected to netpie....");
    if(client.connect(CLIENT_ID,TOKEN,SECRET)){
      Serial.println("Connected to netpie");
    }else{
         Serial.print("failed with state:");
          Serial.println(client.state());
          delay(2000);
    }
  }
  // client.publish(TOPIC,"Hello ntpt eiei");

  client.subscribe(Sub_TOPIC);
  Serial.println("Meddage Sub_TOPIC");
}
const char* RED = "OFF";
const char* GREEN = "OFF";
const char* BLUE = "OFF";
const char* ledStatusStr = "";
void callback(char* topic,byte* payload,unsigned int length){
  char* buffer = (char*)malloc(length+1);
  memcpy(buffer,payload,length);
  buffer[length] = '\0';
  Serial.printf("Message %s\n",buffer);
  if(strcmp(buffer,"on")==0){
    digitalWrite(LED_PIN,LOW);
    ledStatus = true;
    ledStatusStr = "on";
  }
   else if(strcmp(buffer,"off")==0){
    digitalWrite(LED_PIN,HIGH);
    ledStatus = false;
    ledStatusStr = "off";
  }
  else if(strcmp(buffer,"RED")==0){
    Serial.printf("%s\n", COLOR_NAMES[0]);
    analogWrite(RED_PIN, COLORS[state][0]);
    analogWrite(GREEN_PIN, COLORS[state][1]);
    analogWrite(BLUE_PIN, COLORS[state][2]);
    RED = "ON";
  }
  else if(strcmp(buffer,"REDOFF")==0){
    analogWrite(RED_PIN, 0);
    RED = "OFF";

  }
  else if(strcmp(buffer,"GREEN")==0){
    Serial.printf("%s\n", COLOR_NAMES[1]);
    analogWrite(RED_PIN, COLORS[1][0]);
    analogWrite(GREEN_PIN, COLORS[1][1]);
    analogWrite(BLUE_PIN, COLORS[1][2]);
    GREEN = "ON";
  }
  else if(strcmp(buffer,"GREENOFF")==0){
    GREEN =  "OFF";
    analogWrite(GREEN_PIN, 0);

  }
    else if(strcmp(buffer,"BLUE")==0){
        Serial.printf("%s\n", COLOR_NAMES[2]);
    analogWrite(RED_PIN, COLORS[2][0]);
    analogWrite(GREEN_PIN, COLORS[2][1]);
    analogWrite(BLUE_PIN, COLORS[2][2]);
     BLUE = "ON";
  }
  else if(strcmp(buffer,"BLUEOFF")==0){
    analogWrite(BLUE_PIN, 0);
    BLUE = "OFF";
  }
  free(buffer);
}

void loop() {
  client.loop();
  delay(500); 
  int ldrValue = analogRead(A0);  // อ่านค่าแสงจาก LDR
  bool buttonStatus = digitalRead(BUTTON_PIN) > 0 ? false :true;
  ledStatusStr = buttonStatus ? "on" : "off";
  // Serial.print("LDR Value: ");

  String data = "{\"data\":{\"ldr\":"+String(ldrValue)+",\"button\":"+
  String(buttonStatus) + ",\"led\":\""+ledStatusStr+"\",\"RED\":\""+RED+"\",\"GREEN\":\""
  +GREEN+"\",\"BLUE\":\""+BLUE+"\"}}";


  Serial.println(data);
  client.publish(TOPIC,data.c_str());
}
