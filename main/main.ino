#include <Servo.h>

//设置引脚
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

//我们的云台是逆时针旋转，按照从置物点向取物点看去的视角
float Take_up_angle[6];   // 对应刚开始拿起物体时六个摆臂所需转动角度
float Put_down_angle[6];  // 对应放下物体时六个摆臂所需转动的角度
float Take_up_time[6];              // 对应放下物体时每一个物体要向下运动的距离

int Pwmup = 180;
int Pwmstop = 90; // 用于servo.write
int Pwmdown = 0;



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
    Put_down_angle[i] = 20 + 60 * i;
  }
}



//程序运行
void setup() {
  Serial.begin(9600);

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

void loop() {
  float distance;
  while (Serial.available() == 0) {}
  if ('s' == Serial.read()) {
    for (int i = 0; i++; i < 6) {
      while (Serial.available() == 0) {}
      A[i] = Serial.read() - '0';
    }
    Assignment();
    run_To_take();
    takeAll();
    run_To_put();
    putAll();
  }
}