void setup() {
  // put your setup code here, to run once:
   Serial.begin(115200);
   
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 1; i < 21; i++ ){
    Serial.println(i);
    delay(1000);
  }
}
