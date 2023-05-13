#include <Servo.h>
#include <FlexiTimer2.h>

#define servo1 3
#define servo2 5

int pos = 0;
Servo myservo1;
Servo myservo2;

void setup() {
    //设定串口频率
    Serial.begin(9600);
    myservo1.attach(servo1, 500, 2500);          //修正脉冲宽度
    myservo2.attach(servo2, 500, 2500);          //修正脉冲宽度
}
 
void ser(Servo myservo)
{
  for (pos = 0; pos <= 180; pos += 1) {       //pos+=1等价于pos=pos+1
    myservo.write(pos);
    delay(15);					
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    myservo.write(pos);
    delay(15); 					
  }
}
void loop() {
  while (Serial.available()) {
    int inByte = Serial.read();
    //↑将获取到的内容，例如通过串口输入的是0，变量inByte值实际上为48（ASCII编码）
    //↓则需要转换为字符0，以便后面的程序判断，字符型是单引号，千万不要用成双引号
    char user = (char)inByte;
    if (user == '3') {
      ser(myservo1);
    } 
    else if (user == '5') {
      ser(myservo2);
    } 
    else {
      Serial.println(user);
    }
  }
}