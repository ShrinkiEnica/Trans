// 使用硬件声明6个吸盘，共12个数字接口，6+2个霍尔直流电机，还有一个中间舵机，使用16路扩展板，6个灰度传感器，目前是模拟引脚，我看看有没有数字引脚的
// 总共使用的引脚资源为：后期计算

// 引入头文件，目前引入舵机头文件，用于测试代码
// 定时器库的头文件
#include <Servo.h>
//#include <FlexiTimer2.h>

//设置引脚
//int Trig = 14;     // 发送声波
//int Echo = 15;     // 接收声波
int Panservo = 3;  //PWM
int Servo1 = 4;    //PWM
int Servo2 = 5;    //PWM
int Servo3 = 6;    //PWM
int Servo4 = 7;    //PWM
int Servo5 = 8;    //PWM
int Servo6 = 9;    //PWM

// 控制吸盘吸气的引脚
int Sucker1 = 16;
int Sucker2 = 17;
int Sucker3 = 18;
int Sucker4 = 19;
int Sucker5 = 20;
int Sucker6 = 21;

// 控制吸盘排气的引脚
int Suckero1 = 22;
int Suckero2 = 23;
int Suckero3 = 24;
int Suckero4 = 25;
int Suckero5 = 26;
int Suckero6 = 27;

//电机控制，目前是想让两个电机接到一个输出口，后期可能会改成两个
int Motor1a = 10;  // PWM波输入
int Motor1b = 11;  // PWM波输入
int Motor2a = 12;
int Motor2b = 13;
//#define FG_Pin2 3                    // 霍尔信号，Uno共两个外部中断引脚，2引脚为中断0，3引脚为中断1
//#define Motor2 6                     // PWM波输入
//#define Direction2 8                 // 换向线，感觉白线是换向线

//设置全局变量,如果变量要在中断中访问，要使用volatile进行申明
int A[6];               // 对应各个物体是可乐还是箱子
float CocaTime = 0;     // 提起可乐舵机运动的时间
float BoxTime[3];       // 提起箱子舵机运动的时间

Servo panservo;  // 底盘舵机结构体，还是对象
Servo myservo1;  // 吸盘舵机对象
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;
Servo myservo6;

Servo moservo1;  // 定义电机结构体对象
Servo moservo2;
Servo moservo3;
Servo moservo4;

/*
int setDistance[2] = { 40, 40 };  // 对到取物点和置物点减速距离
int exaDistance[2] = { 10, 10 };  // 精确距离
float Vhigh = 1.0;                // 直流电机速度
float Vlow = 0.1;
*/

//我们的云台是逆时针旋转，按照从置物点向取物点看去的视角
float Take_up_angle[6];   // 对应刚开始拿起物体时六个摆臂所需转动角度
float Put_down_angle[6];  // 对应放下物体时六个摆臂所需转动的角度
float Take_up_time[6];              // 对应放下物体时每一个物体要向下运动的距离

int Pwmup = 180;
int Pwmstop = 90; // 用于servo.write
int Pwmdown = 0;

//int m = 0;  // 用于对任务进行分段
// 0, 从中点到取物处，并进行可乐和箱子的判断
// 1, 进行各个摆臂的微调,，舵机控制光轴向下，中央舵机旋转，真空阀吸气
// 2，向放置点运行，提升高度，中央舵机的旋转,
// 3，放置，
// 4，结束，复位，可能有可能没有
int n = 0;  //用于防止小车在exadistance附近反复横跳

/*
//函数声明
//该函数用于返回距离
float Distance() {
  float time1;
  float time2;
  float Time;
  float distance;
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  while (digitalRead(Echo) == LOW)
    ;                //等待高电平信号，
  time1 = micros();  //高电平信号触发，记录当前时间
  while (digitalRead(Echo) == HIGH)
    ;                //等待底电平信号
  time2 = micros();  //低电平信号触发，记录当前时间
  //Serial.println("函数调用");
  Time = time2 - time1;
  distance = Time / 58.0;  //单位厘米 distance = Time1*340*100/1000000/2;
  return (distance);       //返回时间差即引脚高电平所持续的时间
}
*/

void run_To_take() {
  // 控制两个电机同时正转
  digitalWrite(Motor1a, HIGH);
  digitalWrite(Motor1b, LOW);
  digitalWrite(Motor2a, HIGH);
  digitalWrite(Motor2b, LOW);
  delay(10);  // 调参确定走的距离
}

void run_To_put() {
  // 控制两个电机同时反转
  digitalWrite(Motor1a, LOW);
  digitalWrite(Motor1b, HIGH);
  digitalWrite(Motor2a, LOW);
  digitalWrite(Motor2b, HIGH);
  delay(10);  // 调参确定走的距离
}


// 这一套是假设对称分布的，即夹角为60度
// type 为 提起的物品的类型 1为可乐，0为箱子
void takeUp(int type, Servo myservo, int PinSucker) {
  int time = 0;                                             // 舵机向下运动的时间
  time = (type == 1) ?  CocaTime: BoxTime[PinSucker - 16];  //如果为可乐，向下运动多少，如果为箱子，运动多少
  myservo.write(Pwmdown);                                   // 使舵机带动机构向下动
  delay(time);
  digitalWrite(PinSucker, HIGH);                            // 吸气
  myservo.write(Pwmup);                                     // 使舵机带动机构向上动
  delay(time);
}

// time 为 舵机下转的时间
void putDown(int type, Servo myservo, int PinSucker) {
  int time = 0;
  time = (type == 1) ?  10: 20;                             //如果为可乐，向下运动多少，如果为箱子，运动多少
  myservo.write(Pwmdown);                                   //舵机带动机械臂向下运动
  delay(time);
  digitalWrite(PinSucker, HIGH);                            // 排气，松开物体
  delay(1000);                                              // 给它排气的时间
  myservo.write(Pwmup);                                     //舵机带动机械臂向上运动
  delay(time);
}

// 提起所有箱子
// panservo 是底盘的舵机
// 关键在于angle[6]，用它来确定提起每一个物品所需转动的角度
//void takeAll(float angle[6], Servo panservo) {
void takeAll() {
  panservo.write(Take_up_angle[0]);
  delay(1000);  // 可能不需要
  takeUp(0, myservo1, Sucker1);

  panservo.write(Take_up_angle[1]);
  delay(1000);
  takeUp(0, myservo2, Sucker2);

  panservo.write(Take_up_angle[2]);
  delay(1000);
  takeUp(0, myservo3, Sucker3);

  panservo.write(Take_up_angle[3]);
  delay(1000);
  takeUp(1, myservo4, Sucker4);

  panservo.write(Take_up_angle[4]);
  delay(1000);
  takeUp(1, myservo5, Sucker5);

  panservo.write(Take_up_angle[5]);
  delay(1000);
  takeUp(1, myservo6, Sucker6);
}

//void putAll(float angle[6], Servo panservo) {
void putAll() {
  panservo.write(Put_down_angle[0]);
  delay(1000);  // 可能不需要
  putDown(0, myservo1, Suckero1);

  panservo.write(Put_down_angle[1]);
  delay(1000);
  putDown(0, myservo2, Suckero2);

  panservo.write(Put_down_angle[2]);
  delay(1000);
  putDown(0, myservo3, Suckero3);

  panservo.write(Put_down_angle[3]);
  delay(1000);
  putDown(1, myservo4, Suckero4);

  panservo.write(Put_down_angle[4]);
  delay(1000);
  putDown(1, myservo5, Suckero5);

  panservo.write(Put_down_angle[5]);
  delay(1000);
  putDown(1, myservo6, Suckero6);
}

void Assignment(){
  int i = 0,j = 0,k = 3;
  for(i = 0;i < 6;i++){
    if(A[i] == 0){
      Take_up_angle[j] = 360 - (36 * i - 60 * j);
      if(Take_up_angle[j] >= 360){
        Take_up_angle[j] = Take_up_angle[j] - 360;
      }
      j++;
    }
    else{
      Take_up_angle[k] = 360 - (36 * i - 60 * k);
      k++;
    }
  }
  for(i = 0;i < 6;i++){
    Put_down_angle[i] = 20 + 60 * i;  //显然我们的180度云台做不到
  }
}


/*
//这一套为非对称安装,但是并没有写完
// type 为 提起的物品的类型 1为可乐，0为箱子
void takeUp(int type, Servo myservo, int PinSucker) {
  myservo.write(Pwmdown);                                   // 使舵机带动机构向下动
  delay(10);
  digitalWrite(PinSucker, HIGH);                            // 吸气
  myservo.write(Pwmup);                                     // 使舵机带动机构向上动
  delay(time);
}

// time 为 舵机下转的时间
void putDown(int type, Servo myservo, int PinSucker) {
  int time = 0;
  time = (type == 1) ?  10: 20;                             //如果为可乐，向下运动多少，如果为箱子，运动多少
  myservo.write(Pwmdown);                                   //舵机带动机械臂向下运动
  delay(time);
  digitalWrite(PinSucker, HIGH);                            // 排气，松开物体
  delay(1000);                                              // 给它排气的时间
  myservo.write(Pwmup);                                     //舵机带动机械臂向上运动
  delay(time);
}

void takeAll(){
  takeUp(A[0], myservo1, Sucker1);
  takeUp(A[1], myservo2, Sucker2);
  takeUp(A[2], myservo3, Sucker3);
  takeUp(A[3], myservo4, Sucker4);
  takeUp(A[4], myservo5, Sucker5);
  takeUp(A[5], myservo6, Sucker6);
  delay(500);
}

void putAll(){
  putDown(A[0], myservo1, Suckero1);
  putDown(A[1], myservo2, Suckero2);
  putDown(A[2], myservo3, Suckero3);
  putDown(A[3], myservo4, Suckero4);
  putDown(A[4], myservo5, Suckero5);
  putDown(A[5], myservo6, Suckero6);
  delay(500);
}

void Assignment() {
  int i = 0,j = 0,k = 0;
  for(i = 0;i < 6;i++){
    if(A[i] == 0){
      Put_down_angle[j] = (36 * i + 30);
      j++;
    }
    else{
      put_down_angle[(k+3)] = (36 * i + 20);
      k++;
    }
  }
}
*/




//程序运行
void setup() {
  // Serial.begin(9600);              // 先写上，但我估计我们应该是用不到串口调试的
  //pinMode(Trig, OUTPUT);  // 配置声波传感器
  //pinMode(Echo, INPUT);

  pinMode(Motor1a, OUTPUT);
  pinMode(Motor1b, OUTPUT);
  pinMode(Motor2a, OUTPUT);
  pinMode(Motor2b, OUTPUT);

  panservo.attach(Panservo, 500, 2500);
  myservo1.attach(Servo1, 500, 2500);
  myservo2.attach(Servo2, 500, 2500);
  myservo3.attach(Servo3, 500, 2500);
  myservo4.attach(Servo4, 500, 2500);
  myservo5.attach(Servo5, 500, 2500);
  myservo6.attach(Servo6, 500, 2500);
  moservo1.attach(Motor1a, 500, 2500);  //修正脉冲宽度
  moservo2.attach(Motor1b, 500, 2500);
  moservo3.attach(Motor2a, 500, 2500);  //修正脉冲宽度
  moservo4.attach(Motor2b, 500, 2500);
}


/***********************方案一*************************/
// 具体来说，不进行超声波测距，转而通过对转速乘时间的提前计算进行开环控制
void loop() {
  float distance;
  if (Serial.available()) {
    if ('s' == Serial.read()) {
      for (int i = 0; i++; i < 6) {
        A[i] = Serial.read();
      }
      Assignment();
      run_To_take();
      //takeAll(Take_up_angle, panservo);
      takeAll();
      run_To_put();
      //putAll(Put_down_angle, panservo);
      putAll();
      exit(0);
    }
  }
}
/***********************方案二*************************/
//带有距离传感器的闭环控制
/*
void loop() {
  float distance;
  if (Serial.available()) {
    if ('s' == Serial.read()) {
      for(int i = 0;i++;i < 6)
      {
        A[i] = Serial.read();
      }
      do {
        // 读取声波传感器距离
        // if大于setDistance[0],小车高速运行，pid调速
        // if小于等于setDistance[0],减速到预定值
        // if==exaDistance[0],停下,进行灰度检测,并对A进行赋值，i++，此时i = 1
        // if小于exaDistance[0],以极小速度反转，pid调速,n++
        distance = Distance();
        if (distance > setDistance[0]) {
          run_To_take();
        }
        if (distance == setDistance[0]) {
          takeAll(Take_up_angle,panservo);
        }
        if (distance < setDistance[0]) {
        }
      } while (m = 0 && n < 3);
      // if虽然跳出了以上循环但是仍然有i==0，对于这种，我们补充进行灰度检测，（虽然这个位置还是不对劲，但是我们默认他没问题），进行赋值并i++，此时i = 1
      // 此处编译一个双void函数，用于控制根据A的结果而判断各个手臂提升高度
      // 大致思路为：
      // if(A[0] == 0)，h[0] = 1,w[0] = 1
      // else
      // 同时执行提升操作，但不执行旋转操作
      // ...
      // if(A[5] == 0)，h[5] = 1,w[5] = 1
      // else
      // 同时执行提升操作，但不执行旋转操作
      // 完毕后，i++，此时i = 2
      n = 0;  //用于防止小车在exadistance附近反复横跳
      do {
        // 读取声波传感器距离
        // if大于setDistance[0],小车高速运行，pid调速
        // if小于等于setDistance[0],减速到预定值
        // if==exaDistance[0],停下，i++，此时i = 3
        // if小于exaDistance[0],以极小速度反转，pid调速,n++
        distance = Distance();
        distance = Distance();
        if (distance > setDistance[0]) {
          run_To_put();
        }
        if (distance == setDistance[0]) {
          putAll(Put_down_angle,panservo);
        }
        if (distance < setDistance[0]) {
        }
      } while (m = 0 && n < 3);
      // if虽然跳出了以上循环但是仍然有i==0，对于这种，我们补充i++，此时i = 3，（虽然这个位置还是不对劲，但是我们默认他没问题）
      // 此处编译一个双void函数，用于控制根据A的之前的分配数据旋转，并松开吸盘，i++
      // 结束
      exit(0);
    }
  }
}
*/
