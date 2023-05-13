/*
char ss;
int i = 10;

void setup() {
  Serial.begin(9600);   //设置串口速度
  pinMode(13, OUTPUT);  //一般13口上都有一个已经接好的LED，所以用这个口子，少接些元件
}

void loop() {
  if (i > 0)  //启动时的开关信号，这样可以避免主程序陷入死循环
  {
    Serial.print('a');  //先向从机发一个‘a’，
    i = 0;
  }
  ss = Serial.read();  //再读串口，接受从机的字符‘b’
  if (ss == 'b') {
    digitalWrite(13, HIGH);
    delay(300);
    digitalWrite(13, LOW);
    delay(300);  //让13脚的LED闪烁
    ss = 0;
    i = 10;  //让i重新赋值
  }
}
*/

int TX = 1;
int RX = 0;
int Trig = 2;
int Echo = 3;
int ExR = 4;
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

void Stop()
{
  do{
  }while(!digitalRead(RX));  
}

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  pinMode(ExR, OUTPUT);
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
    digitalWrite(ExR,HIGH);
    Stop();
  }
  //让程序先在这里结束，做一个试发行版本
  //因为没办法处理ExR，HIGH；只要改成LOW就会再次触发另一单片机中断
  //也许可以通过改变中断触发条件解决，但是目前不确定，先这么来
  //exit(0);
}
