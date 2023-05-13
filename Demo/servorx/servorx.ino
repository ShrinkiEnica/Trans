/*
#include <Servo.h>
Servo myservo;
char ss;
int pos = 0;
int i = 0;
int servopin = 10;

void setup() {
  Serial.begin(9600);
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
}

void loop() {
  ss = Serial.read();
  if (ss == 'a') {
    for (pos = 0; pos <= 180; pos += 1) {  //pos+=1等价于pos=pos+1
      myservo.write(pos);
      delay(15);
    }
    for (pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(15);
    }
    i++;
    if (i == 3) {
      Serial.print('b');  //收到‘a\'后向主机发一个’b\'
      exit(0);
    }
  }
}
*/

#include <Servo.h>
Servo myservo;
int RX = 0;
int TX = 1;
int pos = 0;
int servopin = 10;
int ExT = 9;

void servoRun() {
  for (pos = 0; pos <= 180; pos += 1) {  //pos+=1等价于pos=pos+1
    myservo.write(pos);
    delay(10);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(10);
  }
  digitalWrite(ExT,HIGH);
  delay(5);
  digitalWrite(ExT,LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(ExT,OUTPUT);
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
}

void loop() {
  attachInterrupt(RX,servoRun,CHANGE);
  exit(0);
}