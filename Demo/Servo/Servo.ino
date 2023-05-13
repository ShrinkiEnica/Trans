#include <Servo.h>            //加载文件库
int pos = 0;
Servo myservo;
int servopin = 46;
int i = 0;
 
void setup()
{
  myservo.attach(servopin, 500, 2500);          //修正脉冲宽度
}
 
void loop()
{
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
}
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