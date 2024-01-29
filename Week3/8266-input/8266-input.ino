#define BUTTON_PIN 4
#define BAUD_RATE 115200

void setup() {
  // put your setup code here, to run once:
    Serial.begin(BAUD_RATE);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("\nReady");

}

void loop() {
  // put your main code here, to run repeatedly:
    int data;
    data = digitalRead(BUTTON_PIN);
    Serial.printf("DATA : %d\n", data);
    delay(1000);
}
