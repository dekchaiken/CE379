#define BUTTON_PIN 4
#define LDR_PIN A0
#define BAUD_RATE 115200


void setup() {
  // put your setup code here, to run once:
    Serial.begin(BAUD_RATE);
    // pinMode(BUTTON_PIN, INPUT_PULLUP);
    Serial.println("\nReady");

}

void loop() {
  // put your main code here, to run repeatedly:
    // int data;
    // data = digitalRead(BUTTON_PIN);
    // Serial.printf("DATA : %d\n", data);
    // delay(1000);
    int intensity;
    intensity = analogRead(LDR_PIN);
    Serial.printf("Intensity : %d\n", intensity);
    delay(1000);
}
