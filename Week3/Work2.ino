#define BUTTON_PIN 4
#define LDR_PIN A0
#define LED_PIN 2
#define BAUD_RATE 115200


void setup() {
  // put your setup code here, to run once:
    Serial.begin(BAUD_RATE);
    pinMode(LED_PIN, OUTPUT);
    Serial.println("\nReady");

    unsigned long startTime = 0;
    unsigned long stopTime = 0;
    unsigned long elapsedTime = 0;
    // pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  int buttonState = digitalRead(BUTTON_PIN);

  if (buttonState == HIGH) {
    // ปุ่มถูกปล่อย
  } else {
    // ปุ่มถูกกด
    if (startTime == 0) {
      // กดปุ่มครั้งแรก เริ่มจับเวลา
      startTime = millis();
      Serial.println("เริ่มจับเวลา");
    } else {
      // กดปุ่มครั้งที่สอง หยุดการจับเวลา
      stopTime = millis();
      elapsedTime = stopTime - startTime;
      Serial.print("หยุดจับเวลา เวลา: ");
      Serial.print(elapsedTime / 1000);
      Serial.println(" วินาที");
      startTime = 0;
    }
  }
}
