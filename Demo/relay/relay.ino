#include <Servo.h>  //加载文件库
int pos = 0;
Servo myservo;
int servopin = 3;
int relay = 52;

void setup() {
  Serial.begin(9600);
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
  pinMode(relay, OUTPUT);
}

void loop() {
  digitalWrite(relay, HIGH);
  delay(10000);
  digitalWrite(relay, LOW);
  delay(2500);
  exit(0);
}