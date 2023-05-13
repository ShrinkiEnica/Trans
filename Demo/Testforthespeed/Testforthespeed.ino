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