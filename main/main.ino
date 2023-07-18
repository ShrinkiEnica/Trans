#include <Servo.h> //加载文件库

class Center_servo
{
private:
    Servo center_servo;
    int pin;
    int angle;
    int relay_pin;

public:
    Center_servo(int pin, int relay_pin, int angle)
    {
        this->pin = pin;
        this->angle = angle;
        this->relay_pin = relay_pin;
    }
    void run_to(int run_to_angle)
    {
        // 设置每次要转的角度，顺时针2度和逆时针2度
        int interval = run_to_angle >= angle ? 1 : -1;
        // 设置要转的次数
        int times = (run_to_angle - angle) / interval;
        for (int i = 0; i < times; i++)
        {
            center_servo.write(angle + i * interval);
            delay(40);
        }
        // 更新变量
        // 更新变量的时间不需要那么长
        delay(5);
        angle = run_to_angle;
    }
    void init(int reset_angle = 180 / 2)
    {
        digitalWrite(relay_pin, HIGH);
        center_servo.write(reset_angle);
        // 更新变量
        delay(5);
        angle = reset_angle;
    }

    void relay_enable()
    {
        digitalWrite(relay_pin, HIGH);
    }

    void write(int run_to_angle)
    {
        center_servo.write(run_to_angle);
        angle = run_to_angle;
    }

    void attach(int attach_pin, int var1, int var2)
    {
        center_servo.attach(attach_pin, var1, var2);
    }
};

class Sucker
{
private:
    int pin;

public:
    Sucker(int pin)
    {
        this->pin = pin;
    }
    void suck()
    {
        digitalWrite(pin, HIGH);
    }
    void exhale()
    {
        digitalWrite(pin, LOW);
    }
};

class Motor
{
private:
    int pos_pin;
    int neg_pin;

public:
    Motor(int pos_pin, int neg_pin)
    {
        this->pos_pin = pos_pin;
        this->neg_pin = neg_pin;
    }
    void run_backward(int duty_cycle)
    {
        analogWrite(neg_pin, duty_cycle * 255 / 100);
        digitalWrite(pos_pin, LOW);
    }
    void run_forward(int duty_cycle)
    {
        analogWrite(pos_pin, duty_cycle * 255 / 100);
        digitalWrite(neg_pin, LOW);
    }
    void stop()
    {
        digitalWrite(pos_pin, LOW);
        digitalWrite(neg_pin, LOW);
    }
};

class Servo_class
{
private:
    Servo my_servo;
    int stable_angle;
    int pin;

public:
    Servo_class(int pin, int stable_angle = 92)
    {
        this->pin = pin;
        this->stable_angle = stable_angle;
    }

    void quick_up(int time)
    {
        my_servo.write(170);
        delay(time);
        my_servo.write(stable_angle);
    }
    void stop(int stable_angle = 92)
    {
        my_servo.write(stable_angle);
    }
    void write_up()
    {
        my_servo.write(170);
    }

    void write_down()
    {
        my_servo.write(10);
    }
    void quick_down(int time)
    {
        my_servo.write(10);
        delay(time);
        my_servo.write(stable_angle);
    }
    void attach(int attach_pin, int pulse_width_start, int pulse_width_end)
    {
        my_servo.attach(attach_pin, pulse_width_start, pulse_width_end);
        pin = attach_pin;
    }
};

class Claw
{
private:
    int pin;
    int release_angle;
    int grab_angle;
    int time;
    Servo my_servo;

public:
    Claw(int release_angle, int grab_angle)
    {
        this->release_angle = release_angle;
        this->grab_angle = grab_angle;
        this->time = 2000;
    }

    void grab()
    {
        my_servo.write(grab_angle);
        delay(time);
    }
    void release()
    {
        my_servo.write(release_angle);
        delay(time);
    }
    void attach(int attach_pin, int val1, int val2)
    {
        my_servo.attach(attach_pin, val1, val2);
        pin = attach_pin;
    }
};

//{ 引脚定义
const int motor_pos_pin = 8;
const int motor_neg_pin = 9;

const int center_servo_pin = 10;
const int center_servo_relay_pin = 50;

const int sucker_22_pin = 51;
const int sucker_12_pin = 52;
const int sucker11_pin = 53;

const int claw_21_pin = 5;
const int claw_31_pin = 6;
const int claw_32_pin = 7;

const int servo_1_pin = 2;
const int servo_2_pin = 3;
const int servo_3_pin = 4;
//}

// 有用的全局变量定义
// 判断是箱子还是可乐的数组
// 由于历史遗留问题，1和2替换一下
int coke_0_box_1[6] = {0, 1, 0, 0, 1, 1};
// int angles_1_1[6] = {108, 144, 180, 218, 252, 288};
// int angles_2_1[6] = {232, 266, 302, 338, 14, 52};
// int angles_3_1[6] = {350, 26, 60, 98, 134, 170}; // 第四个有问题,第三个小了
/* 这是有7个的情况*/
int angles_1_1[7] = {72,108, 144, 180, 218, 252, 288};
int angles_2_1[7] = {200,232, 266, 302, 338, 14, 52};               int center_angles[6] = {160, 160, 160, 160, 160, 160};
int angles_3_1[7] = {320,350, 26, 60, 98, 134, 170}; // 第四个有问题,第三个小了

int put_to_left_angles[6] = {214, 176, 94, 60, 334, 300};
int put_to_right_angles[6] = {304, 266, 184, 150, 64, 30};
            
int device_use_sequence[6] = {};
int item_take_sequence[6] = {};


// 轮子电机、中央舵机、吸盘电机、悬臂电机类的初始化{
Motor My_motor(motor_pos_pin, motor_neg_pin);
Center_servo center_servo(center_servo_pin, center_servo_relay_pin, 180 / 2);

Sucker sucker_22(sucker_22_pin);
Sucker sucker_12(sucker_12_pin);
Sucker sucker11(sucker11_pin);
Claw claw22(30, 90);
Claw claw11(20, 100);
Claw claw12(40, 110);

Servo_class servo_1(servo_1_pin, 91);
Servo_class servo_2(servo_2_pin);
Servo_class servo_3(servo_3_pin, 92);
//}

// 这个函数目前看来似乎使用不到
/*
void take_all()
{
    int angle_sucker_11[6] = {};
    int angle_sucker_12[6] = {};
    int angle_sucker_22[6] = {};
    int angle_claw_21[6] = {};
    int angle_claw_31[6] = {};
    int angle_claw_32[6] = {};
}
*/

void initiate()
{
    int time_begin = millis();
    servo_1.write_up();
    servo_2.write_up();
    servo_3.write_up();
    while (millis() - time_begin < 1500)
        ;
    servo_1.stop();
    servo_2.stop();
    servo_3.stop();

    center_servo.relay_enable();
    center_servo.write(180 / 2);
    delay(8000);
}

/*
void put_all()
{
    int coke_angles[6] = {170 / 2, 190 / 2, 290 / 2, 325 / 2, 10 / 2, 45 / 2};
    int box_angles[6] = {60 / 2, 95 / 2, 185 / 2, 195 / 2, 308 / 2, 308 / 2};
    Sucker suckers[6] = {
        sucker_11,
        sucker_12,
        sucker_22,
        };
    Servo_class servos[3] = {
        servo_1,
        servo_2,
        servo_3};
    // 由于箱子有高度，所以每次舵机下降的时间要变短
    int box_down_times[3] = {1000, 500, 0};
    int already_put_boxes = 0;
    int cola_down_times;
    // 判断当前的sucker是可乐还是箱子，并放下
    for (int i = 0; i < 6; i++)
    {
        // 如果是可乐
           if (coke_0_box_1[i] == 0){
           center_servo.run_to(coke_angles[i]);
           servos[i/2].slow_down(cola_down_times);
           suckers[i].exhale();
           delay(1000);
           }
        // 如果是箱子
        if (coke_0_box_1[i] == 1)
        {
            center_servo.run_to(box_angles[i]);
            servos[i / 2].slow_down(box_down_times[already_put_boxes]);
            suckers[i].exhale();
            delay(1000);
            already_put_boxes++;
        }
    }
}
*/

void test_center()
{
}

void test_servo()
{
}

void test_claw()
{
    servo_1.quick_up(1500);
    claw22.release();
    delay(1000);
    servo_1.quick_down(1000);
    claw22.grab();
    delay(500);
    servo_1.quick_up(1000);
}

void test_assignment()
{
    int m = 0;
    int n = 0;
    int temp = -1;
    int mark = -1;
    for (int i = 0; i < 6; i++)
    {
        if (i == 0)
            // 如果是第一次，那么对temp初始化
            temp = coke_0_box_1[0];
        else
        {
            if (temp == coke_0_box_1[i] && 1 == temp)
            {
                center_angles[0] = angles_1_1[i - 1];
                center_angles[1] = angles_1_1[i - 1];
                m = i;
                mark++;
            }
            else if (temp == coke_0_box_1[i] && 0 == temp)
            {
                center_angles[2] = angles_3_1[i - 1];
                center_angles[3] = angles_3_1[i - 1];
                n = i;
                mark++;
            }
        }
    }
    for (int j = 0; j < 6; j++)
    {
        if (mark)
        {
            if (1 == coke_0_box_1[j] && m != j && (m - 1) != j)
            {
                center_angles[4] = angles_2_1[j];
            }
            else if (0 == coke_0_box_1[j] && n != j && (n - 1) != j)
            {
                center_angles[5] = angles_2_1[j - 1];
            }
        }
        else if (coke_0_box_1[0])
        {
        }
        else if (!coke_0_box_1[0])
        {
        }
    }
}

void minimal_assignment(){

}

void test_array(int *angle_array)
{
    for (int i = 0; i < 6; i++)
    {
        center_servo.run_to(angle_array[i] / 2);
        delay(2000);
    }
}

void test_logic()
{
}

void run_to_put()
{
    My_motor.run_backward(80);
    // 4600
    delay(5500);
    My_motor.stop();
}

void run_to_take()
{
    My_motor.run_forward(80);
    delay(2650);
    My_motor.stop();
}
void setup()
{
    Serial.begin(9600);
    // 修正脉冲宽度
    pinMode(motor_neg_pin, OUTPUT);
    pinMode(motor_pos_pin, OUTPUT);

    pinMode(sucker11_pin, OUTPUT);
    pinMode(sucker_12_pin, OUTPUT);
    pinMode(sucker_22_pin, OUTPUT);

    pinMode(center_servo_relay_pin, OUTPUT);
    center_servo.attach(center_servo_pin, 500, 2500);

    claw22.attach(claw_21_pin, 500, 2500);
    claw11.attach(claw_31_pin, 500, 2500);
    claw12.attach(claw_32_pin, 500, 2500);

    servo_1.attach(servo_1_pin, 500, 2500);
    servo_2.attach(servo_2_pin, 500, 2500);
    servo_3.attach(servo_3_pin, 500, 2500);
}

void loop()
{
    // 跑路时间
    delay(2000);
    
    while(1){
        if (Serial.available())
        {
            delay(100);
            if (Serial.read() == 's')
            {
                for (int i = 0; i < 6; i++)
                {
                    device_use_sequence[i] = Serial.read() - '0';
                }
                for (int i = 0; i < 6; i++)
                {
                    item_take_sequence[i] = Serial.read() - '0';
                }
                break;
            }
        }
    }
    // 
    

    My_motor.run_backward(100);
    delay(4900);
    My_motor.stop();

    delay(10000);

    exit(0);
}
