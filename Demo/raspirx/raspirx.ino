#include <Servo.h>  //加载文件库
int pos = 0;
Servo myservo;
int servopin = 46;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() == 0) {}
  //Serial.println("Serial is available");
  if ('s' == Serial.read()) {
    Serial.println("Hello Raspi,i am arduino");
    while (Serial.available() == 0) {}
    char A = Serial.read();
    int a = A - '0';
    Serial.println("1");
    while (Serial.available() == 0) {}
    char B = Serial.read();
    int b = B - '0';
    Serial.println("0");
    if (a == 1 && b == 0) {
      for (pos = 0; pos <= 180; pos += 1) {  //pos+=1等价于pos=pos+1
        myservo.write(pos);
        delay(15);
      }
      for (pos = 180; pos >= 0; pos -= 1) {
        myservo.write(pos);
        delay(15);
      }
    }
  }
}
