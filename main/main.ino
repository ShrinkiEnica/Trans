#include <Servo.h> //加载文件库
#include "sequences.h"
#include "class.h"

//{ 引脚定义
const int motor_pos_pin = 8;
const int motor_neg_pin = 9;

const int center_servo_pin = 10;
const int center_servo_relay_pin = 36;

const int sucker_32_pin = 37;
const int sucker_12_pin = 52;
const int sucker_11_pin = 53;

const int claw_31_pin = 5;
const int claw_21_pin = 45;
const int claw_22_pin = 7;

const int servo_1_pin = 2;
const int servo_2_pin = 3;
const int servo_3_pin = 4;

//}

// 有用的全局变量定义
// 判断是箱子还是可乐的数组
// 由于历史遗留问题，1和2替换一下
int func[6] = {-1, -1, -1, -1, -1, -1};
int coke_0_box_1[6] = {1,0,1,0,1,0};
//int angles_1_1[6] = {108, 144, 180, 218, 252, 288};
//int angles_2_1[6] = {232, 266, 302, 338, 14, 52};
//int angles_3_1[6] = {350, 26, 60, 98, 134, 170}; // 第四个有问题,第三个小了

/* 这是有7个的情况*/
int angles_1_1[7] = {72, 108, 144, 180, 218, 252, 288};
int angles_3_1[7] = {320, 350, 26, 60, 98, 134, 170}; // 第四个有问题,第三个小了
int angles_2_1[7] = {200, 232, 266, 302, 338, 14, 52};
int center_angles[6] = {160, 160, 160, 160, 160, 160};



int put_to_left_angles[6] = {334,300,214,176,94,60};
int put_to_right_angles[6] = {68,34,308,270,188,154};

const int stack_up_time = 1500;
const int box_up_time = 700;

int *device_use_sequence = NULL;
int *item_take_sequence = NULL;

// 轮子电机、中央舵机、吸盘电机、悬臂电机类的初始化{
Motor My_motor(motor_pos_pin, motor_neg_pin);
Center_servo center_servo(center_servo_pin, center_servo_relay_pin, 180 / 2);

Sucker sucker11(sucker_11_pin);
Sucker sucker12(sucker_12_pin);
Sucker sucker32(sucker_32_pin);
Claw claw21(20, 100);
Claw claw22(15, 90);
Claw claw31(30, 90);

Servo_class servo_1(servo_1_pin, 91);
Servo_class servo_2(servo_2_pin);
Servo_class servo_3(servo_3_pin, 92);
//}

void take_all(){
    // 需要用到的参数为center_angles和device_use_sequence
    // 当在一个角度有两个东西需要夹取时，设计标志变量，标志已经转的次数
    // int already_turn = 0;
    for (int i = 0; i < 6 ;i++){
        int device_index = device_use_sequence[i];
        delay(1000);
        center_servo.run_to(center_angles[i]);
        switch (device_index)
        {
        case 0:
            sucker11.suck();
            servo_1.quick_down(1000);
            delay(2000);
            servo_1.quick_up(1000);
        case 1:
            sucker12.suck();
            servo_1.quick_down(1000);
            delay(2000);
            servo_1.quick_up(1000);
            break;
        case 2:
            servo_2.quick_down(1000);
            claw21.grab();
            delay(1000);
            servo_2.quick_up(1000);
            break;
        case 3:
            servo_2.quick_down(1000);
            claw21.grab();
            delay(1000);
            servo_2.quick_up(1000);
            break;
        case 4:
            servo_3.quick_down(1000);
            claw31.grab();
            delay(1000);
            servo_3.quick_up(1000);
            break;
        case 5:
            sucker32.suck();
            servo_3.quick_down(1000);
            delay(3000);
            servo_3.quick_up(1000);
            break;
        default:
            break;
        }
    }
}

void Serial_receive()
{
    while (1)
    {
        if (Serial.available())
        {
            delay(100);
            if (Serial.read() == 's')
            {
                for (int i = 0; i < 6; i++)
                {
                    // device_use_sequence[i] = Serial.read() - '0';
                    coke_0_box_1[i] = Serial.read() - '0';
                }
                /*
                for (int i = 0; i < 6; i++)
                {
                    item_take_sequence[i] = Serial.read() - '0';
                }
                */
                break;
            }
        }
    }
}

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
    claw21.release();
    claw22.release();
    claw31.release();

    center_servo.relay_enable();
    center_servo.write(180 / 2);
    delay(4000);
}

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

int assign_num(int index)
{
    if (index == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void minimal_assignment()
{
    for (int i = 0; i < 20; i++)
    {
        bool is_same = 1;
        for (int j = 0; j < 6; j++)
        {
            if (psequences_array[i]->item_layout_sequence[j] != coke_0_box_1[j])
            {
                is_same = false;
                break;
            }
        }
        if (is_same)
        {
            device_use_sequence = psequences_array[i]->device_use_sequence;
            item_take_sequence = psequences_array[i]->item_take_sequence;
            break;
        }
    }
    for (int i = 0; i < 6; i++)
    {
        int index = device_use_sequence[i] % 2;
        if (device_use_sequence[i] / 2 == 0)
        {
            // 如果位于2号臂，那么要从第二位开始，即索引为1的地方开始
            center_angles[i] = angles_1_1[item_take_sequence[i] + assign_num(index)];
        }
        if (device_use_sequence[i] / 2 == 1)
        {
            center_angles[i] = angles_2_1[item_take_sequence[i] + assign_num(index)];
        }
        if (device_use_sequence[i] / 2 == 2)
        {
            center_angles[i] = angles_3_1[item_take_sequence[i] + assign_num(index)];
        }
    }
}

void normal_assignment()
{
    int cot[6] = {-1, -1, -1, -1, -1, -1};
    int m = -1;
    int n = -1;
    int k = -1;
    int c = 0;
    int d = 0;
    int temp = -1;
    // int mark = -1;
    for (int i = 0; i < 6; i++)
    {
        if (temp == -1)
        {
            // 如果是第一次，那么对temp初始化
            temp = coke_0_box_1[i];
        }
        else
        {
            if (temp == coke_0_box_1[i] && 1 == temp)
            {
                // cout << "h"<< endl;
                func[c] = 1;
                center_angles[c++] = angles_1_1[i - 1];
                func[c] = 2;
                center_angles[c++] = angles_1_1[i - 1];
                temp = -1;
                m = 1;
                cot[i] = 1;
                cot[i - 1] = 1;
                // mark++;
            }
            else if (temp == coke_0_box_1[i] && 0 == temp)
            {
                // cout << "l" << endl;
                func[c] = 3;
                center_angles[c++] = angles_3_1[i - 1];
                func[c] = 4;
                center_angles[c++] = angles_3_1[i - 1];
                temp = -1;
                n = 1;
                cot[i] = 1;
                cot[i - 1] = 1;
                // mark++;
            }
            else if (0 == temp && 1 == coke_0_box_1[i] && k != 1)
            {
                func[c] = 5;
                center_angles[c++] = angles_2_1[i - 1];
                func[c] = 6;
                center_angles[c++] = angles_2_1[i - 1];
                temp = -1;
                cot[i] = 1;
                cot[i - 1] = 1;
                k = 1;
                // m = 2;
                // n = 2;
                // mark++;
            }
            else
            {
                temp = coke_0_box_1[i];
            }
        }
    }
    for (int j = 0; j < 6; j++)
    {
        if (1 == coke_0_box_1[j] && cot[j] != 1)
        {
            if (1 == m)
            {
                func[c] = 6;
                center_angles[c++] = angles_2_1[j];
            }
            else if (-1 == m)
            {
                func[c] = 1;
                center_angles[c++] = angles_1_1[j];
                m++;
            }
            else if (0 == m)
            {
                func[c] = 2;
                center_angles[c++] = angles_1_1[j - 1];
                m++;
            }
        }
        else if (0 == coke_0_box_1[j] && cot[j] != 1)
        {
            if (1 == n)
            {
                func[c] = 5;
                center_angles[c++] = angles_2_1[j - 1];
            }
            else if (-1 == n)
            {
                func[c] = 3;
                center_angles[c++] = angles_3_1[j];
                n++;
            }
            else if (0 == n)
            {
                func[c] = 4;
                center_angles[c++] = angles_3_1[j - 1];
                n++;
            }
        }
    }
}

void logic()
{
    delay(5000);
    for (int i = 0; i < 6; i++)
    {
        center_servo.run_to(center_angles[i] / 2);
        delay(2000);
        switch (func[i])
        {
        case 1:
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        }
    }
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

void put_all()
{
    Claw *claw_list[3] = {&claw21, &claw22, &claw31};
    Sucker *sucker_list[3] = {&sucker11, &sucker12, &sucker32};
    for (int start = millis(); millis() - start < 700;){
        servo_1.write_up();
        servo_2.write_up();
        servo_3.write_up();
    }
    servo_1.stop();
    servo_2.stop();
    servo_3.stop();

    center_servo.run_to(put_to_left_angles[2]/2);
    servo_2.quick_down(700);
    claw21.release();
    delay(500);
    servo_2.quick_up(700);

    center_servo.run_to(put_to_left_angles[3]/2);
    servo_2.quick_down(700);
    claw22.release();
    servo_2.quick_up(700);
    
    center_servo.run_to(put_to_left_angles[4]/2);
    servo_3.quick_down(700);
    claw31.release();
    delay(500);
    servo_3.quick_up(700);

    center_servo.run_to(put_to_right_angles[5]/2);
    sucker32.exhale();
    delay(500);
    servo_3.quick_up(1400);

    servo_1.quick_up(600);

    center_servo.run_to(put_to_right_angles[0]/2);
    sucker11.exhale();
    delay(500);
    servo_1.quick_up(500);


    center_servo.run_to(put_to_right_angles[1]/2);
    sucker12.exhale();
    delay(500);
}


void setup()
{
    Serial.begin(9600);
    // 修正脉冲宽度
    pinMode(motor_neg_pin, OUTPUT);
    pinMode(motor_pos_pin, OUTPUT);

    pinMode(sucker_11_pin, OUTPUT);
    pinMode(sucker_12_pin, OUTPUT);
    pinMode(sucker_32_pin, OUTPUT);

    pinMode(center_servo_relay_pin, OUTPUT);
    center_servo.attach(center_servo_pin, 500, 2500);

    claw31.attach(claw_31_pin, 500, 2500);
    claw21.attach(claw_21_pin, 500, 2500);
    claw22.attach(claw_22_pin, 500, 2500);

    servo_1.attach(servo_1_pin, 500, 2500);
    servo_2.attach(servo_2_pin, 500, 2500);
    servo_3.attach(servo_3_pin, 500, 2500);
}

void loop()
{
    minimal_assignment();
    // 跑路时间
    delay(2000);
    initiate();
    delay(2000);

    take_all();

    //

    // for (int i = 0 ; i < 7; i++){
    //  center_servo.run_to(angles_3_1[i]/2);
    //  delay(3000);
    // }

    delay(10000);

    exit(0);
}
