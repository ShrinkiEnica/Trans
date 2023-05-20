#include <Servo.h>  //加载文件库
int pos = 0;
Servo myservo;

int servopin = 9;
int Motor1a = 10;  // PWM波输入
int Motor1b = 11;  // PWM波输入

int Motor2a = 5;  // PWM波输入
int Motor2b = 6;  // PWM波输入
int i = 0;

void setup() {
  myservo.attach(servopin, 500, 2500);  //修正脉冲宽度
  pinMode(Motor1a,OUTPUT);
  pinMode(Motor1b,OUTPUT);
  pinMode(Motor2a,OUTPUT);
  pinMode(Motor2b,OUTPUT);
}

void loop() {
  digitalWrite(Motor1a, HIGH);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, HIGH);  //控制电机正转
  digitalWrite(Motor2b, LOW);
  delay(1500);

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);  //控制电机正转
  digitalWrite(Motor2b, LOW);

  exit(0);
}
/*
//双路版本
  digitalWrite(Motor1a, HIGH);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, HIGH);  //控制电机正转
  digitalWrite(Motor2b, LOW);
  delay(500);

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, LOW);  //控制电机正转
  digitalWrite(Motor2b, LOW);

  exit(0);
  */
/*
//直流电机测试版
  digitalWrite(Motor1a, HIGH);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  delay(500);

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  delay(500);

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, HIGH);
  delay(500);

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  delay(2500);

  analogWrite(Motor1a, 100);  //控制电机正转
  delay(2500);

  analogWrite(Motor1a, 150);  //控制电机正转
  delay(2500);

  analogWrite(Motor1a, 255);  //控制电机正转

  digitalWrite(Motor1a, LOW);  //控制电机正转
  digitalWrite(Motor1b, LOW);
  delay(500);
  */
/*
//360度舵机特供版
  myservo.write(80);
  delay(5000);
  myservo.write(0);
  delay(2500);
  myservo.write(90);
  delay(2500);
  myservo.write(100);
  delay(5000);
  myservo.write(180);
  delay(2500);
  exit(0);
  */
/*
  myservo.write(0);
  delay(2500);
  myservo.write(45);
  delay(2500);
  myservo.write(90);
  delay(2500);
  myservo.write(135);
  delay(2500);
  myservo.write(180);
  delay(2500);
  exit(0);
*/
/*
  myservo.write(60);
  delay(15);
  */

/*
  for (pos = 0; pos <= 180; pos += 1) {       //pos+=1等价于pos=pos+1
    myservo.write(pos);
    delay(15);					
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(5); 					
  }
  i++;
  if(i == 3)
  {
    exit(0);
  }
  */