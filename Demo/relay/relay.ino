#include <Servo.h>  //加载文件库
int pos = 0;
Servo myservo;
int servopin = 3;
int relay = 4;

void setup() {
  Serial.begin(9600);
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
  pinMode(relay, OUTPUT);
}

void loop() {

  for (pos = 0; pos <= 180; pos += 1) {  //pos+=1等价于pos=pos+1
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(relay, HIGH);
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
  for (pos = 0; pos <= 180; pos += 1) {  //pos+=1等价于pos=pos+1
    myservo.write(pos);
    delay(15);
  }
  digitalWrite(relay, LOW);
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15);
  }
}