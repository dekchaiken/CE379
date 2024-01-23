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
float f1, f2;
char ch;

void loop() {
  lab202();
}

void lab202() {
  switch (state) {
    case 0:
      if(!flag){
      Serial.println();
      Serial.println("Ready!!! Please enter first operand");
      flag = true;
    }
      if(Serial.available() > 0 ){
        f1 = Serial.parseFloat();
        if(f1 !=0){
          state++;    
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
      if (!flag) {
        Serial.println("Please enter the operator (+, -, *, /):");
        flag = true;
      }
      if (Serial.available() > 0) {
        ch = Serial.read(); 
        if(ch >= '0' && ch <= '9'){
          Serial.println("Invalid operator");
          state = 2;
        } else {
          state++;
          flag = false;
        }
      } else {
        state = 2;
      }
      break;

    case 3:  
      switch (ch) {
        case '+':
          Serial.printf("The result of %f + %f = %f\n", f1, f2, f1 + f2);
          break;
        case '-':
          Serial.printf("The result of %f - %f = %f\n", f1, f2, f1 - f2);
          break;
        case '*':
          Serial.printf("The result of %f * %f = %f\n", f1, f2, f1 * f2);
          break;
        case '/':
          if (f2 != 0) { 
            Serial.printf("The result of %f / %f = %f\n", f1, f2, f1 / f2);
          } else {
            Serial.println("Error");
          }
          break;
        default:
          Serial.println("Invalid operator");
      }
      state = 0;  
      break;

    default:
      state = 0;
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