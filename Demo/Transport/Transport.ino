/*
#define IN1 3  //定义IN1为3口
#define IN2 4  //定义IN2为4口
#define  ENA  10 //定义ENA为10口
void setup()
{  
  pinMode(IN1,OUTPUT);
  pinMode(IN2,OUTPUT);
  pinMode(ENA,OUTPUT);
}
void loop()
{   //正转速度为满速的 200/255
  digitalWrite(IN1,HIGH);  //控制电机正转
  digitalWrite(IN2,LOW);
  analogWrite(ENA,200);   //控制电机转速，迳我自己测试超过150电机才开始转

  delay(5000);
  digitalWrite(IN1,LOW);   //电机反转
  digitalWrite(IN2,HIGH);
  analogWrite(ENA,200);
    
  delay(5000);
  digitalWrite(IN1,LOW); //控制电机停下
  digitalWrite(IN2,LOW); 
  analogWrite(ENA,255); 
   
}
*/


/*

  【Arduino】166种传感器模块系列实验（79）

  实验七十九： 模拟灰度传感器 （反射式光电模块）

  OUT——A0 读取串口灰度模拟数值

  板载灯——D13

*/

/*
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT); 
}

void loop()
{
  int val;
  val=analogRead(0);  
  Serial.println(val,DEC);    
  delay(1000);
}
*/


/*
  【Arduino】66种传感器模块系列实验（79）
  实验七十九： 模拟灰度传感器 （反射式光电模块）
  OUT——A0 
  板载灯——D13
  程序之二，控制板载灯，低灰度时灯暗，反之灯亮
*/

/*
int Led = 13; 
int buttonpin = A0;
int val;

void setup()
{
pinMode(Led, OUTPUT); 
pinMode(buttonpin, INPUT); 
}

void loop()
{
val = digitalRead(buttonpin); 
if (val == HIGH) 
{
digitalWrite(Led, HIGH);
}
else
{
digitalWrite(Led, LOW);
}
}
*/


/*********************************************************************
 ——————1.开发环境：Arduino IDE——————————————————————————————————
 ——————2.使用开发板型号：Arduino Mega 2560——————————————————————
 ——————3.电机型号：36GP BLDC3525直流无刷电机内置霍尔驱动（五线）—
*********************************************************************/
#include <FlexiTimer2.h>             //定时器库的头文件

// 引脚命名
#define FG_Pin 20                  // 霍尔信号，对应外部中断编号3
#define Motor 22                   // PWM波输入
#define Direction 24               // 换向线

// 定义变量,如果变量要在中断中访问，要使用volatile进行申明
uint16_t counter = 0;             // 霍尔信号计数器
volatile int16_t speed = 0;       // 定义转速

// 中断函数
void counterISR(){
  counter++;    // 计数+1
}

// 把计数器置零
void resetCounter(){
    measurement();
    counter = 0;
}

// 计算测量到的电机转速
long measurement( ){
  /* 
   * 此电机一圈输出9个脉冲信号，计时0.5s,测一次速度，计算信号变化的次数，转化为转速(rpm) 
   */
  speed = counter/9/0.5*60;  
  Serial.print("当前转速:");
  Serial.print(speed);
  Serial.println("r/min"); 
}

void setup() {
 
  Serial.begin(115200);
  pinMode(FG_Pin,INPUT);
  pinMode(Motor,OUTPUT);
  pinMode(Direction,OUTPUT);

  attachInterrupt(3,counterISR,RISING);      // 外部中断，每次上升沿触发一次中断，便计一次数
  
  FlexiTimer2::set(500,resetCounter);       // 定时器中断，中断设置函数，每 500ms 进入一次中断，计算一次转速
  FlexiTimer2::start();                		// 开始计时
}

void loop() {
    digitalWrite(Direction,HIGH);     		// 设置旋转方向,高电平逆时针转,方向为负  
    digitalWrite(Motor, HIGH);
    delayMicroseconds(100); 				// 此时占空比100%，频率10KHz
    digitalWrite(Motor, LOW);
    delayMicroseconds(100 - 0); 			// 修改这里的100可以调整频率，可知，方波周期为100微妙
}
/*  ************************************** */
/*
*/
/*  ************************************** */

#define VCC 2
#define PLS 3
#define DIR 4
#define ENA 5

void setup() {
	pinMode(VCC, OUTPUT);
	pinMode(PLS, OUTPUT);
	pinMode(DIR, OUTPUT);
	pinMode(ENA, OUTPUT);
}

void loop() {
	digitalWrite(VCC, HIGH);
	digitalWrite(ENA, HIGH);
	digitalWrite(DIR, HIGH);	//正转
	//正转一圈，用时1s
	//此处驱动器定义1600步为1圈
	//本来1600X625微秒=1秒，因为时间间隔太短，程序运行也需要时间，间隔时间/2之后总时间差不多1秒
    for(int x=0; x<1600; x++){
	    digitalWrite(PLS, HIGH);
	    delayMicroseconds(625/2);
	    digitalWrite(PLS, LOW);
	    delayMicroseconds(625/2);
    }
	delay(1000);	//停1s
	
	digitalWrite(DIR, LOW);    //反转
	//反转一圈，用时1s
    for(int x=0; x<1600; x++){
	    digitalWrite(PLS, HIGH);
	    delayMicroseconds(625/2);
	    digitalWrite(PLS, LOW);
	    delayMicroseconds(625/2);
    }
	delay(1000);	//停1s
}
