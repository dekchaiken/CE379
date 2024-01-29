#define BUTTON_PIN 4 // กำหนดหมายเลขพินสำหรับปุ่ม
#define BAUD_RATE 115200 // กำหนดอัตราบิตสำหรับการสื่อสาร Serial

unsigned long startTime = 0; // ตัวแปรสำหรับเก็บเวลาเริ่มต้น
unsigned long endTime = 0; // ตัวแปรสำหรับเก็บเวลาสิ้นสุด
bool timer = false; // ตัวแปรสถานะสำหรับการจับเวลา
bool buttonState = HIGH; // ตัวแปรสถานะปุ่มก่อนหน้า

enum ButtonState { // ประกาศ enum สำหรับสถานะปุ่ม
  BUTTON_WAIT, // รอการกดปุ่ม
  BUTTON_PRESSED, // กดปุ่ม
  BUTTON_RELEASED // ปล่อยปุ่ม
};

ButtonState buttonState = BUTTON_WAIT; // ตั้งค่าสถานะปุ่มเริ่มต้น

void setup() {
  Serial.begin(BAUD_RATE); // เริ่มต้นการสื่อสาร Serial
  pinMode(BUTTON_PIN, INPUT_PULLUP); // ตั้งค่าพินปุ่มเป็น INPUT กับ pull-up resistor
  Serial.println("\nReady"); // พิมพ์ข้อความ "Ready" บน Serial
}

void loop() {
  int buttonStateRaw = digitalRead(BUTTON_PIN); // อ่านสถานะปุ่มปัจจุบัน

  if (buttonStateRaw != buttonState) {
    delay(50); // ตรวจสอบว่าสถานะปุ่มเปลี่ยนแปลงหรือไม่
  }

  switch (buttonState) { // ตรวจสอบสถานะปุ่มปัจจุบัน
    case BUTTON_WAIT:
      if (buttonStateRaw == LOW && buttonState == HIGH) { // กดปุ่ม
        buttonState = BUTTON_PRESSED; // เปลี่ยนสถานะเป็น BUTTON_PRESSED
        startTime = millis(); // เก็บเวลาเริ่มต้น
        Serial.println("Timer started."); // พิมพ์ข้อความเริ่มเจับเวลาบน Serial
      }
      break;

    case BUTTON_PRESSED:
      if (buttonStateRaw == HIGH) { // ปล่อยปุ่ม
        buttonState = BUTTON_RELEASED; // จะเปลี่ยนสถานะเป็น BUTTON_RELEASED
      }
      break;

    case BUTTON_RELEASED:
      if (buttonStateRaw == LOW) { // กดปุ่มอีกครั้ง
        buttonState = BUTTON_WAIT; // เปลี่ยนสถานะเป็น BUTTON_WAIT
        endTime = millis(); // เก็บเวลาสิ้นสุด
        timer = false; // หยุดการจับเวลา

        // คำนวณและแสดงเวลาที่ผ่านไป
        float elapsedTime = (endTime - startTime) / 1000.0;
        Serial.printf("Elapsed time: %.3f seconds\n", elapsedTime);

        // รีเซ็ตเวลาเริ่มต้นและสิ้นสุด
        startTime = 0;
        endTime = 0;
      }
      break;
  }
  // อัปเดตสถานะปุ่ม
  buttonState = buttonStateRaw;
}