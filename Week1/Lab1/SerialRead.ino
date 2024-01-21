void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
}

void loop() {
  // ตรวจสอบว่ามีข้อมูลรอรับอยู่หรือไม่
  if (Serial.available() > 0) {
    // รับค่าจาก Serial monitor
    char c = Serial.read();

    // ตรวจสอบว่าค่าที่รับมาคือ A หรือ a
    if (c == 'A' || c == 'a') {
      // ตอบกลับด้วยข้อความ "Hello"
      Serial.println("Hello");
    } else if (c == 'Z' || c == 'z') {
      // ตอบกลับด้วยข้อความ "Good bye"
      Serial.println("Good bye");
    } else {
      // ตอบกลับด้วยข้อความ "I don't know"
      Serial.println("I don't know");
    }
  }
}
