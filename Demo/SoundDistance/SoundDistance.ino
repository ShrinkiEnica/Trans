/*
#include <HCSR04.h>
UltraSonicDistanceSensor distanceSensor(2, 3);  // 初始化引脚，第一个参数为Trig引脚，第二个参数为Echo引脚。
float cm;
void setup () {
  Serial.begin(9600);  // 打开串口监视器
}
void loop () {
  cm = distanceSensor.measureDistanceCm();
  //Serial.println(cm);//打印超声波测量距离，单位为厘米
  //delay(500);//每个0.5s打印一次
  if(cm >= 40)
  {
    Serial.println(cm);
  }
}
*/


int Trig = 2;
int Echo = 3;
float distance;
//获取超声波往返时间函数，发送到接收
int times() {
  int time1;
  int time2;
  while (digitalRead(Echo) == LOW);//等待高电平信号，
  time1 = micros();//高电平信号触发，记录当前时间
  while (digitalRead(Echo) == HIGH);//等待底电平信号
  time2 = micros();//低电平信号触发，记录当前时间
  //Serial.println("函数调用");
  return (time2 - time1);//返回时间差即引脚高电平所持续的时间
}
void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
}
void loop() {
  //发送一个10us的脉冲
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  //获取时间
  //program_one
  int Time1 = times();
  //program_two
  int Time2 = pulseIn(Echo, HIGH); //获取超声波返回时长，单位us = 10^-6s
  //计算距离
  distance =  Time1 / 58; //单位厘米 distance = Time1*340*100/1000000/2;
  //Serial.print(distance);
  //Serial.println("cm");
  //delay(1000);
  if(distance >= 40)
  {
    Serial.println(distance);
  }
}
