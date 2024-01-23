#define BAUD_RATE 115200
void setup() {
  Serial.begin(BAUD_RATE);
}

// Available States
// 0: Start
// 1: Opr1
// 2: Opr2
// 3: End

int state = 0;
bool flag = false;
float f1, f2, f3, f4, f5;

void loop() {
  lab202();
}



void lab202() {
  switch (state) {
    case 0:         //Begin State
    if(!flag){
      Serial.println();
      Serial.println("Ready!!! Please enter first operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f1 = Serial.parseFloat();
        if(f1 !=0){
          state++;    //Change from Start to Opr1
          flag = false;
        }
      }
      delay(50);
      break;
    case 1:
    if(!flag){
      Serial.println("Please enter 2 operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f2 = Serial.parseFloat();
        if(f2 !=0){
          state++;
          flag = false;
        } else {
          Serial.println("Invalid operand");
          Serial.println("Please enter 2 ooperand");
          //flag = true;
        }
      }
      delay(50);
      break;
    case 2:
    if(!flag){
      Serial.println("Please enter 3 operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f3 = Serial.parseFloat();
        if(f3 !=0){
          state++;
          flag = false;
        } else {
          Serial.println("Invalid operand");
          Serial.println("Please enter 3 ooperand");
          //flag = true;
        }
      }
      delay(50);
      break;
    case 3:
    if(!flag){
      Serial.println("Please enter 4 operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f4 = Serial.parseFloat();
        if(f4 !=0){
          state++;
          flag = false;
        } else {
          Serial.println("Invalid operand");
          Serial.println("Please enter 4 ooperand");
          //flag = true;
        }
      }
      delay(50);
      break;
    case 4:
    if(!flag){
      Serial.println("Please enter 5 operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f5 = Serial.parseFloat();
        if(f5 !=0){
          state++;
          flag = false;
        } else {
          Serial.println("Invalid operand");
          Serial.println("Please enter 5 ooperand");
          //flag = true;
        }
      }
      delay(50);
      break;
    case 5:
    if(!flag){
      Serial.printf("The result of %f + %f + %f +%f +%f = %f", f1, f2, f3, f4, f5, (f1 + f2 + f3 + f4 + f5)/5);
      state = 3;
      flag = true;
    }
      break;
    default:
      state = 0;
      flag = false;
      break;
  }
  delay(50);
}



void lab201() {
  int x = 1;
  if(Serial.available() > 0) {
      float a = Serial.parseFloat();
      Serial.printf("The input data is %f\n", a);
  }
}