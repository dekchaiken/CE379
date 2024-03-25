#define BLYNK_TEMPLATE_ID "TMPL6DVoaTfQA"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "SdXthv4JqPWzahTbtbCX0L-YYXYgaeQi"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
// #include <DHT.h>

#define BAUD_RATE 115200
#define LED_PIN 2
// #define DHT_PIN D4
#define INTERVAL 1000
#define LDR_PIN A0
#define RED_PIN 15
#define GREEN_PIN 12
#define BLUE_PIN 13


const char* ssid = "KenNoluv"; 
const char* password = "11111111";



// DHT dht(DHT_PIN, DHT11);
BlynkTimer timer;
int ldr_value = 0;


// void timerEvent(){
//   float temp = dht.readTemperature();
//   if(!isnan(temp)) {
//     Blynk.virtualWrite(V4, temp);    //virtualWrite ใช้กับ virtualPin
//     Serial.println(temp);
//   }
// }

void ldrTest(){
  ldr_value = analogRead(LDR_PIN);
  if(!isnan(ldr_value)) {
    Blynk.virtualWrite(V4, ldr_value);    //virtualWrite ใช้กับ virtualPin
    Serial.println(ldr_value);
  }
}

void setup() {
  //put your setup code here
  Serial.begin(BAUD_RATE);
  //dht.begin();
  pinMode(LED_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  digitalWrite(LED_PIN, OUTPUT);
  pinMode(LDR_PIN, INPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, password);
  timer.setInterval(INTERVAL, ldrTest);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println('\n');
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
}

BLYNK_WRITE(V0){
  int value = param.asInt();
  analogWrite(RED_PIN, value);
}
BLYNK_WRITE(V1){
  int value = param.asInt();
  analogWrite(GREEN_PIN, value);
}
BLYNK_WRITE(V2){
  int value = param.asInt();
  analogWrite(BLUE_PIN, value);
}

bool initialized = false;

void loop() {
  Blynk.run();
  timer.run();
  if(!initialized) {
    Blynk.virtualWrite(V4, WiFi.localIP().toString());
  }
}