#include <Servo.h>  //加载文件库
#include <SoftwareSerial.h>

class Center_servo {
private:
    Servo center_servo;
    int pin;
    int relay_pin;

public:
    int angle;
    Center_servo(int pin, int relay_pin, int angle) {
        this->pin = pin;
        this->angle = angle;
        this->relay_pin = relay_pin;
    }
    void run_to(int run_to_angle) {
        // 设置每次要转的角度，顺时针2度和逆时针2度
        int interval = run_to_angle >= angle ? 1 : -1;
        // 设置要转的次数
        int times = (run_to_angle - angle) / interval;
        for (int i = 0; i < times; i++) {
            center_servo.write(angle + i * interval);
            delay(60);
            //40
        }
        // 更新变量
        // 更新变量的时间不需要那么长
        delay(5);
        angle = run_to_angle;
    }
    void slow_run_to(int run_to_angle) {
        // 设置每次要转的角度，顺时针2度和逆时针2度
        int interval = run_to_angle >= angle ? 1 : -1;
        // 设置要转的次数
        int times = (run_to_angle - angle) / interval;
        for (int i = 0; i < times; i++) {
            center_servo.write(angle + i * interval);
            delay(80);
        }
        // 更新变量
        // 更新变量的时间不需要那么长
        delay(5);
        angle = run_to_angle;
    }
    void very_slow_run_to(int run_to_angle) {
        // 设置每次要转的角度，顺时针2度和逆时针2度
        int interval = run_to_angle >= angle ? 1 : -1;
        // 设置要转的次数
        int times = (run_to_angle - angle) / interval;
        for (int i = 0; i < times; i++) {
            center_servo.write(angle + i * interval);
            delay(130);
        }
        // 更新变量
        // 更新变量的时间不需要那么长
        delay(5);
        angle = run_to_angle;
    }
    void accelerate_run_to(int run_to_angle) {
        int delta_angle = run_to_angle - this->angle;
        int begin_angle = this->angle;
        run_to(begin_angle + (int)(0.5 * delta_angle));
        slow_run_to(begin_angle + (int)(0.7 * delta_angle));
        very_slow_run_to(begin_angle + delta_angle);
    }
    void init(int reset_angle = 180 / 2) {
        digitalWrite(relay_pin, HIGH);
        center_servo.write(reset_angle);
        // 更新变量
        delay(5);
        angle = reset_angle;
    }

    void relay_enable() {
        digitalWrite(relay_pin, HIGH);
    }

    void write(int run_to_angle) {
        center_servo.write(run_to_angle);
        angle = run_to_angle;
    }

    void attach(int attach_pin, int var1, int var2) {
        center_servo.attach(attach_pin, var1, var2);
    }
};

class Sucker {
private:
    int pin;

public:
    Sucker(int pin) {
        this->pin = pin;
    }
    void suck() {
        digitalWrite(pin, HIGH);
    }
    void exhale() {
        digitalWrite(pin, LOW);
    }
};

class Motor {
private:
    int pos_pin;
    int neg_pin;

public:
    Motor(int pos_pin, int neg_pin) {
        this->pos_pin = pos_pin;
        this->neg_pin = neg_pin;
    }
    void run_backward(int duty_cycle) {
        analogWrite(neg_pin, duty_cycle * 255 / 100);
        digitalWrite(pos_pin, LOW);
    }
    void run_forward(int duty_cycle) {
        analogWrite(pos_pin, duty_cycle * 255 / 100);
        digitalWrite(neg_pin, LOW);
    }
    void stop() {
        digitalWrite(pos_pin, LOW);
        digitalWrite(neg_pin, LOW);
    }
};

class Servo_class {
private:
    Servo my_servo;
    int stable_angle;
    int pin;

public:
    Servo_class(int pin, int stable_angle = 92) {
        this->pin = pin;
        this->stable_angle = stable_angle;
    }

    void quick_up(int time) {
        my_servo.write(170);
        delay(time);
        my_servo.write(stable_angle);
    }
    void stop(int stable_angle = 92) {
        my_servo.write(stable_angle);
    }
    void write_up() {
        my_servo.write(170);
    }

    void write_down() {
        my_servo.write(10);
    }
    void quick_down(int time) {
        my_servo.write(10);
        delay(time);
        my_servo.write(stable_angle);
    }
    void attach(int attach_pin, int pulse_width_start, int pulse_width_end) {
        my_servo.attach(attach_pin, pulse_width_start, pulse_width_end);
        pin = attach_pin;
    }

    void write(int stable_angle) {
        my_servo.write(stable_angle);
    }
};

class Claw {
private:
    int pin;
    int release_angle;
    int grab_angle;
    int time;
    Servo my_servo;

public:
    Claw(int release_angle, int grab_angle) {
        this->release_angle = release_angle;
        this->grab_angle = grab_angle;
        this->time = 200;
    }

    void grab() {
        my_servo.write(grab_angle);
    }
    void release() {
        my_servo.write(release_angle);
    }
    void litrel() {
        my_servo.write((grab_angle - 12));
    }

    void write(int a = 10) {
        my_servo.write(a);
    }

    void attach(int attach_pin, int val1, int val2) {
        my_servo.attach(attach_pin, val1, val2);
        pin = attach_pin;
    }
};

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

int coke_0_box_1[6] = {0,1,0,1,0,1};
//{ 1, 0, 1, 0, 1, 0 }存在顺序问题

int angles_1_1[7] = { 74, 110, 142, 178, 214, 250, 286 };
//{ 70, 112, 146, 184, 220, 254, 290 }
int angles_2_1[7] = { 312, 350, 26, 58, 94, 132, 168 };
// { 314, 352, 24, 60, 102, 136, 170 };
int angles_3_1[7] = { 196, 228, 264, 300, 334, 14, 48 };
// { 196, 232, 268, 304, 340, 12, 52 };

//3号的3偏小
int func[6] = { -1, -1, -1, -1, -1, -1 };
int index = 0;
int center_angles[6] = { 0, 0, 0, 0, 0, 0 };
/*
int put_to_left_angles[6] = { 334, 298, 222, 172, 92, 60 };  // { 334, 300, 214, 176, 94, 60 };
int put_to_right_angles[6] = { 64, 30, 308, 270, 188, 150 }; // { 68, 34, 308, 270, 188, 154 };
*/

// 轮子电机、中央舵机、吸盘电机、悬臂电机类的初始化{
Motor My_motor(motor_pos_pin, motor_neg_pin);
Center_servo center_servo(center_servo_pin, center_servo_relay_pin, 180 / 2);

Sucker sucker_32(sucker_32_pin);
Sucker sucker_12(sucker_12_pin);
Sucker sucker_11(sucker_11_pin);
Claw claw_31(10, 65);
// (20, 110)
Claw claw_21(0, 48);
Claw claw_22(0, 50);

Servo_class servo_1(servo_1_pin);
Servo_class servo_2(servo_2_pin);
Servo_class servo_3(servo_3_pin);
//}

SoftwareSerial softSerial(12, 13);
// RX, TX

void Serial_receive() {
    while (1) {
        if (softSerial.available()) {
            delay(100);
            if (softSerial.read() == 's') {
                for (int i = 0; i < 6; i++) {
                    coke_0_box_1[i] = softSerial.read() - '0';
                    delay(5);
                }

                break;
            }
        }
    }
}

// 在最后应当放弃使用initiate函数
void initiate() {
    claw_21.release();
    claw_22.release();
    claw_31.release();
    delay(800);
    int time_begin = millis();

    servo_1.write_up();
    servo_2.write_up();
    servo_3.write_up();

    while (millis() - time_begin < 2000) {
        ;
    }
    servo_1.stop();
    servo_2.stop();
    servo_3.stop();

    center_servo.relay_enable();
    center_servo.write(320 / 2);
}

typedef struct {
    int item_layout_sequence[6];
    int device_use_sequence[6];
    int item_take_sequence[6];
} device_item_sequence;

device_item_sequence sequence1{ { 1, 1, 1, 0, 0, 0 }, { 5, 0, 1, 2, 3, 4 }, { 0, 1, 2, 3, 4, 5 } };
device_item_sequence sequence2{ { 1, 0, 1, 1, 0, 0 }, { 4, 5, 1, 2, 3, 0 }, { 1, 2, 3, 4, 5, 0 } };
device_item_sequence sequence3{ { 0, 1, 1, 0, 0, 1 }, { 0, 4, 5, 1, 2, 3 }, { 5, 0, 1, 2, 3, 4 } };
device_item_sequence sequence4{ { 1, 1, 0, 0, 1, 0 }, { 4, 5, 3, 0, 1, 2 }, { 3, 4, 5, 0, 1, 2 } };
device_item_sequence sequence5{ { 1, 1, 0, 0, 0, 1 }, { 0, 1, 2, 3, 4, 5 }, { 0, 1, 2, 3, 4, 5 } };
device_item_sequence sequence6{ { 1, 0, 0, 0, 1, 1 }, { 2, 3, 0, 1, 4, 5 }, { 2, 3, 4, 5, 1, 0 } };
device_item_sequence sequence7{ { 1, 0, 1, 0, 1, 0 }, { 4, 5, 3, 0, 2, 1 }, { 1, 2, 3, 0, 5, 4 } };
device_item_sequence sequence8{ { 1, 0, 0, 1, 0, 1 }, { 4, 5, 0, 2, 1, 3 }, { 2, 3, 5, 4, 0, 1 } };
device_item_sequence sequence9{ { 1, 0, 0, 1, 1, 0 }, { 0, 1, 4, 2, 3, 5 }, { 3, 4, 5, 1, 2, 0 } };
device_item_sequence sequence10{ { 0, 1, 0, 0, 1, 1 }, { 0, 1, 2, 3, 4, 5 }, { 4, 5, 2, 3, 0, 1 } };
device_item_sequence sequence11{ { 1, 0, 1, 0, 0, 1 }, { 0, 4, 5, 2, 3, 1 }, { 5, 1, 2, 3, 4, 0 } };
device_item_sequence sequence12{ { 1, 1, 0, 1, 0, 0 }, { 2, 3, 0, 1, 4, 5 }, { 4, 5, 0, 1, 2, 3 } };
device_item_sequence sequence13{ { 0, 0, 1, 0, 1, 1 }, { 0, 1, 2, 3, 4, 5 }, { 4, 5, 0, 1, 3, 2 } };
device_item_sequence sequence14{ { 0, 1, 1, 0, 1, 0 }, { 0, 1, 4, 5, 2, 3 }, { 1, 2, 3, 4, 0, 5 } };
device_item_sequence sequence15{ { 0, 1, 0, 1, 1, 0 }, { 0, 1, 4, 5, 2, 3 }, { 3, 4, 0, 1, 2, 5 } };
device_item_sequence sequence16{ { 0, 0, 1, 1, 1, 0 }, { 4, 5, 3, 0, 1, 2 }, { 1, 2, 0, 3, 4, 5 } };
device_item_sequence sequence17{ { 0, 1, 0, 1, 0, 1 }, { 0, 4, 5, 3, 1, 2 }, { 5, 2, 3, 0, 1, 4 } };
device_item_sequence sequence18{ { 0, 0, 0, 1, 1, 1 }, { 4, 5, 0, 1, 2, 3 }, { 2, 3, 4, 5, 0, 1 } };
device_item_sequence sequence19{ { 0, 0, 1, 1, 0, 1 }, { 2, 3, 0, 1, 4, 5 }, { 0, 1, 2, 3, 4, 5 } };
device_item_sequence sequence20{ { 0, 1, 1, 1, 0, 0 }, { 4, 5, 0, 1, 2, 3 }, { 0, 1, 2, 3, 4, 5 } };

device_item_sequence *psequences_array[20] = {
    &sequence1,
    &sequence2,
    &sequence3,
    &sequence4,
    &sequence5,
    &sequence6,
    &sequence7,
    &sequence8,
    &sequence9,
    &sequence10,
    &sequence11,
    &sequence12,
    &sequence13,
    &sequence14,
    &sequence15,
    &sequence16,
    &sequence17,
    &sequence18,
    &sequence19,
    &sequence20
};


void minimal_index() {
    // # 返回组数索引
    for (index = 0; index < 20; index++) {
        bool is_same = 1;
        for (int j = 0; j < 6; j++) {
            if (psequences_array[index]->item_layout_sequence[j] != coke_0_box_1[j]) {
                is_same = false;
                break;
            }
        }
        if (is_same) {
            break;
        }
    }
    // return index + 1;
}

void to_take() {
    My_motor.run_forward(100);
    //2650
    delay(500);
    center_servo.run_to(320 / 2);
    My_motor.run_forward(100);
    delay(3200);
    My_motor.run_forward(45);
    delay(1000);
    My_motor.stop();
}

void to_put() {
    center_servo.run_to(94 / 2);
    My_motor.run_backward(100);
    servo_1.quick_up(1750);
    servo_1.stop(96);
    servo_2.quick_up(200);
    servo_3.quick_up(1200);
    delay(1450);
    My_motor.run_backward(45);
    delay(900);
    My_motor.stop();
}


void put() {
    center_servo.slow_run_to(94 / 2);
    delay(500);
    servo_3.quick_down(400);
    delay(1200);
    claw_31.litrel();
    delay(900);
    servo_3.quick_up(1400);

    center_servo.very_slow_run_to(172 / 2);
    delay(1200);
    servo_2.quick_down(200);
    delay(1200);
    claw_22.litrel();
    delay(900);
    servo_2.quick_up(1600);

    center_servo.slow_run_to(220 / 2);
    delay(1200);
    servo_2.quick_down(1000);
    delay(1200);
    claw_21.litrel();
    delay(900);
    servo_2.quick_up(1800);

    center_servo.slow_run_to(150 / 2);
    servo_3.quick_down(800);
    delay(800);
    sucker_32.exhale();
    delay(1000);
    servo_3.quick_up(900);

    //servo_1.quick_up(500);
    servo_1.stop(96);

    delay(500);
    center_servo.slow_run_to(64 / 2);
    delay(500);
    sucker_11.exhale();
    delay(1000);
    servo_1.quick_up(700);
    servo_1.stop(94);

    center_servo.slow_run_to(30 / 2);
    delay(500);
    sucker_12.exhale();
    delay(1000);
}


void take_1() {
    //抓一个箱子
    center_servo.slow_run_to(192 / 2);
    delay(1200);
    servo_3.quick_down(1550);
    // 2/1950
    sucker_32.suck();
    delay(1500);

    servo_3.quick_up(2100);
    servo_3.stop(93);
    delay(500);

    //抓两个箱子
    center_servo.slow_run_to(142 / 2);
    delay(500);
    //1200
    sucker_11.suck();
    sucker_12.suck();
    servo_1.quick_down(1200);
    //1050
    delay(1000);
    servo_1.quick_up(2100);
    //2650
    servo_1.stop(96);
    delay(500);

    //抓两个可乐
    center_servo.accelerate_run_to(94 / 2);
    delay(1200);
    claw_21.release();
    claw_22.release();
    servo_2.quick_down(1700);
    // 1/ 1650
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2600);
    // 1 /2100
    servo_2.stop(93);
    delay(500);

    //抓一个可乐
    center_servo.slow_run_to(50 / 2);
    delay(1200);
    claw_31.release();
    servo_3.quick_down(1450);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);
}

/*
void take_1_new() {
    //抓一个箱子
    center_servo.slow_run_to(192 / 2);
    servo_3.quick_down(1550);
    // 2/1950
    sucker_32.suck();
    delay(1500);

    for (int start = millis(); millis () - start < 2100;){
        if (millis() - start > 500){
            center_servo.slow_run_to(142/2);
        }
        servo_3.write_up();
    }
    servo_3.stop(93);

    //抓两个箱子
    center_servo.slow_run_to(142 / 2);
    center_servo.angle = 142/2;
    delay(500);
    //1200
    sucker_11.suck();
    sucker_12.suck();
    servo_1.quick_down(1200);
    //1050
    delay(1000);

    servo_1.write_up();
    for (int start = millis(); millis () - start < 2100;){
            if (millis() - start > 500){
                     center_servo.slow_run_to(94/2);
                 }
    }
    servo_1.stop(96);

    delay(500);
    //抓两个可乐
    center_servo.slow_run_to(94 / 2);
    delay(1200);
    claw_21.release();
    claw_22.release();
    servo_2.quick_down(1700);
    // 1/ 1650
    claw_21.grab();
    claw_22.grab();
    delay(1000);

    servo_2.write_up();
    for (int start = millis(); millis () - start < 2600;){
        if (millis() - start > 500){
            center_servo.slow_run_to(50/2);
        }
    }
    // 1 /2100
    servo_2.stop(93);
    delay(50);

    //抓一个可乐
    center_servo.slow_run_to(50 / 2);
    delay(1200);
    claw_31.release();
    servo_3.quick_down(1550);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);
}
*/


void take_2() {
    //101100
    // 抓一个可乐一个箱子
    center_servo.slow_run_to(264 / 2);
    delay(1200);
    claw_31.release();
    sucker_32.suck();
    servo_3.quick_down(1550);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);

    //抓一个箱子
    center_servo.slow_run_to(178 / 2);
    delay(1200);
    servo_1.quick_down(1200);
    // 2/1950
    sucker_12.suck();
    delay(1500);
    servo_1.quick_up(2170);
    servo_1.stop(93);
    delay(500);

    //抓两个可乐
    center_servo.slow_run_to(134 / 2);
    delay(1200);
    claw_21.release();
    claw_22.release();
    servo_2.quick_down(1850);
    // 1/ 1650
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2600);
    // 1 /2100
    servo_2.stop(93);
    delay(500);

    //抓一个箱子
    center_servo.slow_run_to(110 / 2);
    delay(1200);
    servo_1.quick_down(1400);
    // 2/1950
    sucker_11.suck();
    delay(1500);
    servo_1.quick_up(2170);
    servo_1.stop(93);
    delay(500);
}

void take_3() {
    // 011001
    //抓一个箱子
    center_servo.slow_run_to(286 / 2);
    delay(1200);
    servo_1.quick_down(1200);
    // 2/1950
    sucker_11.suck();
    delay(1500);
    servo_1.quick_up(2100);
    servo_1.stop(93);
    delay(500);

    // 抓一个可乐一个箱子
    center_servo.slow_run_to(228 / 2);
    delay(1200);
    claw_31.release();
    sucker_32.suck();
    servo_3.quick_down(1550);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);

    //抓一个箱子
    center_servo.slow_run_to(144 / 2);
    delay(1200);
    servo_1.quick_down(1400);
    // 2/1950
    sucker_12.suck();
    delay(1500);
    servo_1.quick_up(2100);
    servo_1.stop(93);
    delay(500);

    //抓两个可乐
    center_servo.accelerate_run_to(92 / 2);
    delay(1200);
    claw_21.release();
    claw_22.release();
    servo_2.quick_down(1850);
    // 1/ 1650
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2600);
    // 1 /2100
    servo_2.stop(93);
    delay(500);
}

void take_4() {
    //110010
    // 抓一个可乐一个箱子
    center_servo.slow_run_to(336 / 2);
    delay(1200);
    claw_31.release();
    sucker_32.suck();
    servo_3.quick_down(1550);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);

    //抓一个可乐
    center_servo.accelerate_run_to(132 / 2);
    delay(1200);
    claw_22.release();
    servo_2.quick_down(1600);
    // 2/2050
    claw_22.grab();
    delay(2000);
    servo_2.quick_up(2600);
    // 2/3100
    servo_2.stop(93);
    delay(500);

    // 抓起两个箱子
    center_servo.slow_run_to(108 / 2);
    delay(500);
    //1200
    sucker_11.suck();
    sucker_12.suck();
    servo_1.quick_down(1200);
    //1050
    delay(1000);
    servo_1.quick_up(2100);
    //2650
    servo_1.stop(96);
    delay(500);

    //抓一个可乐
    center_servo.slow_run_to(58 / 2);
    delay(1200);
    claw_21.release();
    servo_2.quick_down(1600);
    // 2/2050
    claw_21.grab();
    delay(2000);
    servo_2.quick_up(2600);
    // 2/3100
    servo_2.stop(93);
    delay(500);
}

void take_5() {
    // 110001
    // 抓两个箱子
    center_servo.slow_run_to(110 / 2);
    delay(500);
    //1200
    sucker_11.suck();
    sucker_12.suck();
    servo_1.quick_down(1200);
    //1050
    delay(1000);
    servo_1.quick_up(2100);
    //2650
    servo_1.stop(96);
    delay(500);

    // 抓两个可乐
    center_servo.slow_run_to(60 / 2);
    delay(1200);
    claw_21.release();
    claw_22.release();
    servo_2.quick_down(1600);
    // 1/ 1650
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2600);
    // 1 /2100
    servo_2.stop(93);
    delay(500);

    // 抓一个箱子一个可乐
    center_servo.slow_run_to(14 / 2);
    delay(1200);
    claw_31.release();
    sucker_32.suck();
    servo_3.quick_down(1550);
    //1450
    claw_31.grab();
    delay(2000);
    servo_3.quick_up(2100);
    //1450
    servo_3.stop(93);
    delay(500);
}
void take_6() {
    // 6 item_layout_sequence:[1, 0, 0, 0, 1, 1] device_use_sequence:[4, 0, 1, 5, 2, 3]
    // item_take_sequence:[3, 4, 5, 0, 1, 2] angles:[334, 250, 250, 196, 26, 26] total angle:342 spin times:4
    // 4号爪子拿3号可乐
    center_servo.slow_run_to(336 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);

    // 0,1号吸盘吸4,5号箱子
    center_servo.slow_run_to(250 / 2);
    delay(500);
    servo_1.quick_down(1150);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);

    // 5号吸盘吸0号箱子
    center_servo.slow_run_to(192 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);

    // 2,3号爪子抓1,2可乐
    center_servo.accelerate_run_to(24 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}

void take_7() {
    // 7 item_layout_sequence:[1, 0, 1, 0, 1, 0] device_use_sequence:[4, 5, 0, 3, 1, 2]
    //  item_take_sequence:[3, 4, 2, 5, 0, 1] angles:[334, 334, 178, 132, 74, 26] total angle:342 spin times:5
    // 4爪子5吸盘抓3，4可乐
    center_servo.slow_run_to(336 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 0吸盘抓2箱子
    center_servo.slow_run_to(178 / 2);
    delay(500);
    servo_1.quick_down(1150);
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 3爪子抓5可乐
    center_servo.slow_run_to(134 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 1吸盘抓0箱子
    center_servo.slow_run_to(72 / 2);
    delay(500);
    servo_1.quick_down(1400);
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 2爪子抓1可乐
    center_servo.slow_run_to(26 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}


void take_8() {
    // 8 item_layout_sequence:[1, 0, 0, 1, 0, 1] device_use_sequence:[2, 3, 4, 5, 0, 1]
    // item_take_sequence:[1, 2, 4, 5, 0, 3] angles:[26, 26, 14, 14, 110, 178] total angle:450 spin times:4
    // 2,3爪子抓1，2可乐
    center_servo.slow_run_to(26 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 4爪子5吸盘抓4可乐5箱子
    center_servo.slow_run_to(14 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 0吸盘抓0箱子
    center_servo.slow_run_to(110 / 2);
    delay(500);
    servo_1.quick_down(1150);
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 1吸盘抓3箱子
    center_servo.slow_run_to(180 / 2);
    delay(500);
    servo_1.quick_down(1400);
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
}


void take_9() {
    // 9 item_layout_sequence:[1, 0, 0, 1, 1, 0] device_use_sequence:[0, 1, 5, 4, 2, 3]
    // item_take_sequence:[3, 4, 0, 5, 1, 2] angles:[214, 214, 196, 48, 26, 26] total angle:274 spin times:4
    // 0,1吸盘吸3，4箱子
    center_servo.slow_run_to(214 / 2);
    delay(500);
    servo_1.quick_down(1150);
    sucker_12.suck();
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);

    // 5吸盘吸0箱子
    center_servo.slow_run_to(192 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);

    // 4爪子抓5可乐
    center_servo.slow_run_to(48 / 2);
    delay(500);
    servo_3.quick_down(1350);
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);

    // 2,3抓子抓1，2可乐
    center_servo.slow_run_to(24 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}

void take_10() {
    // 10item_layout_sequence:[0, 1, 0, 0, 1, 1] device_use_sequence:[0, 1, 4, 5, 2, 3]
    // item_take_sequence:[4, 5, 0, 1, 2, 3] angles:[250, 250, 228, 228, 58, 58] total angle:242 spin times:3
    // 0,1吸盘吸4，5箱子
    center_servo.slow_run_to(252 / 2);
    delay(500);
    servo_1.quick_down(1150);
    sucker_12.suck();
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 4爪子5吸盘抓0，1可乐箱子
    center_servo.slow_run_to(230 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 2，3爪子抓2，3可乐
    center_servo.slow_run_to(62 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}


void take_11() {
    // 1 item_layout_sequence:[1, 0, 1, 0, 0, 1] device_use_sequence:[0, 4, 5, 2, 3, 1]
    // item_take_sequence:[5, 1, 2, 3, 4, 0] angles:[286, 264, 264, 94, 94, 74] total angle:246 spin times:4
    // 0吸盘抓5箱子
    center_servo.slow_run_to(286 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 4号爪子,5吸盘抓1号可乐,2号箱子
    center_servo.slow_run_to(264 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 2,3爪子抓3，4可乐
    center_servo.slow_run_to(98 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 1号吸盘吸0号箱子
    center_servo.slow_run_to(74 / 2);
    delay(500);
    servo_1.quick_down(1400);
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
}

void take_12() {
    //12 item_layout_sequence:110100 device_use_sequence:[4, 5, 2, 3, 0, 1] item_take_sequence:[2, 3, 4, 5, 0, 1]
    // angles:[300, 300, 132, 132, 110, 110] total angle:190 spin times:3

    // 5,6 爪子吸盘抓 3,4可乐
    center_servo.accelerate_run_to(298 / 2);
    delay(1000);
    servo_3.quick_down(1550);
    sucker_32.suck();
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 3，4爪子抓5，6可乐
    center_servo.accelerate_run_to(134 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 1,2吸盘抓1，2箱子
    center_servo.slow_run_to(108 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
}

void take_13() {
    //13 item_layout_sequence:001011 device_use_sequence:[2, 3, 4, 5, 0, 1] item_take_sequence:[0, 1, 3, 2, 4, 5]
    //  angles:[350, 350, 334, 264, 250, 250] total angle:150 spin times:4
    // 3,4爪子抓1，2可乐
    center_servo.slow_run_to(350 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 5号爪子抓4号可乐
    center_servo.slow_run_to(334 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 6号吸盘吸3号箱子
    center_servo.slow_run_to(264 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 1,2吸盘吸5，6箱子
    center_servo.slow_run_to(250 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
}

void take_14() {
    // 14 item_layout_sequence:011010 device_use_sequence:[3, 4, 5, 2, 0, 1] item_take_sequence:[0, 3, 4, 5, 1, 2]
    // angles:[312, 334, 334, 168, 142, 142] total angle:226 spin times:4
    // 4号爪子抓1号可乐
    center_servo.slow_run_to(308 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 5号爪子,6号吸盘抓4号可乐,5号箱子
    center_servo.slow_run_to(334 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 3号爪子抓6号可乐
    center_servo.accelerate_run_to(168 / 2);
    delay(500);
    servo_2.quick_down(1700);
    claw_21.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 1,2号吸盘抓2，3号箱子
    center_servo.slow_run_to(142 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
}

void take_15() {
    // 15 item_layout_sequence:010110 device_use_sequence:[4, 5, 0, 1, 3, 2] item_take_sequence:[0, 1, 3, 4, 5, 2]
    // angles:[228, 228, 214, 214, 132, 58] total angle:242 spin times:4

    // 4号爪子5号吸盘抓0可乐1箱子
    center_servo.slow_run_to(228 / 2);
    delay(500);
    servo_3.quick_down(1550);
    sucker_32.suck();
    claw_31.grab();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    // 0,1吸盘抓3，4箱子
    center_servo.slow_run_to(216 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    // 3号爪子抓5号可乐
    center_servo.slow_run_to(132 / 2);
    delay(500);
    servo_2.quick_down(1600);
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    // 2号爪子抓2号可乐
    center_servo.accelerate_run_to(62 / 2);
    delay(500);
    servo_2.quick_down(1600);
    claw_21.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}
void take_16() {
    //16 item_layout_sequence:001110 device_use_sequence:[3, 4, 5, 0, 1, 2] item_take_sequence:[0, 1, 2, 3, 4, 5]
    //angles:[312, 264, 264, 214, 214, 168] total angle:156 spin times:4
    //3抓0位的可乐
    center_servo.slow_run_to(308 / 2);
    delay(500);
    servo_2.quick_down(1600);
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
    //4抓1位可乐且5吸2位吸盘
    center_servo.slow_run_to(264 / 2);
    delay(500);
    servo_3.quick_down(1550);
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);
    servo_3.stop(96);
    //0抓3位箱子且1抓4位箱子
    center_servo.slow_run_to(214 / 2);
    delay(500);
    servo_1.quick_down(1200);
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_1.stop(96);
    //2抓5位可乐
    center_servo.slow_run_to(170 / 2);
    delay(500);
    servo_2.quick_down(1600);
    claw_21.grab();
    delay(1000);
    servo_2.quick_up(2100);
    servo_2.stop(96);
}
void take_17() {
    //17 item_layout_sequence:010101 device_use_sequence:[3, 4, 5, 0, 2, 1] item_take_sequence:[0, 2, 3, 5, 4, 1]
    //angles:[312, 300, 300, 286, 132, 110] total angle:214 spin times:5
    //3号爪子抓0号位
    center_servo.slow_run_to(308 / 2);
    delay(500);                //1200
    servo_2.quick_down(1700);  //1050
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);  //2650
    servo_2.stop(96);

    //4号爪子抓2号位可乐且5号吸盘吸3号位箱子
    center_servo.slow_run_to(300 / 2);
    delay(500);
    servo_3.quick_down(1550);  //1050
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);  //2650
    servo_3.stop(96);

    // 0 号吸盘吸5号位箱子
    center_servo.slow_run_to(286 / 2);
    delay(500);
    servo_1.quick_down(1200);  //1050
    sucker_11.suck();
    delay(1000);
    servo_1.quick_up(2100);  //2650
    servo_1.stop(96);
    // 2号爪子抓4号位可乐
    center_servo.slow_run_to(134 / 2);
    delay(500);
    servo_2.quick_down(1700);  //1050
    claw_21.grab();
    delay(1000);
    servo_2.quick_up(2100);  //2650
    servo_2.stop(96);
    //1号吸盘吸1号位箱子
    center_servo.slow_run_to(108 / 2);
    delay(500);
    servo_1.quick_down(1400);  //1050
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);  //2650
    servo_1.stop(96);
}


void take_18() {
    //18 item_layout_sequence:000111 device_use_sequence:[2, 3, 4, 5, 0, 1] item_take_sequence:[0, 1, 2, 3, 4, 5]
    //angles:[350, 350, 300, 300, 250, 250] total angle:150 spin times:3
    //2号爪子抓0号位且3号爪子抓1号位
    center_servo.slow_run_to(350 / 2);
    delay(500);                //1200
    servo_2.quick_down(1700);  //1050
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);  //2650
    servo_2.stop(96);

    //4号爪子抓2号位可乐且5号吸盘吸3号位箱子
    center_servo.slow_run_to(300 / 2);
    delay(500);
    servo_3.quick_down(1550);  //1050
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);  //2650
    servo_3.stop(96);

    // 0 号吸盘吸4号位箱子且1号吸盘吸5号位
    center_servo.slow_run_to(250 / 2);
    delay(500);
    servo_1.quick_down(1200);  //1050
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);
    servo_3.stop(96);
}
void take_19() {
    //19 item_layout_sequence:001101 device_use_sequence:[2, 3, 0, 1, 4, 5] item_take_sequence:[0, 1, 2, 3, 4, 5]
    //angles:[350, 350, 178, 178, 14, 14] total angle:386 spin times:3
    //2号爪子抓0号位且3号爪子抓1号位
    center_servo.slow_run_to(350 / 2);
    delay(500);                //1200
    servo_2.quick_down(1700);  //1050
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);  //2650
    servo_2.stop(96);

    //0号吸盘吸2号位箱子且1号吸盘吸3号位箱子
    center_servo.slow_run_to(178 / 2);
    delay(500);
    servo_1.quick_down(1200);  //1050
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);  //2650
    servo_1.stop(96);

    //4号爪子抓4号位且5号吸盘吸5号位
    center_servo.slow_run_to(14 / 2);
    delay(500);
    servo_3.quick_down(1550);  //1050
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);  //2650
    servo_3.stop(96);
}
void take_20() {
    //20 item_layout_sequence:011100 device_use_sequence:[4, 5, 0, 1, 2, 3] item_take_sequence:[0, 1, 2, 3, 4, 5]
    //angles:[228, 228, 178, 178, 132, 132] total angle:168 spin times:3
    //4号爪抓0号位且5号吸盘吸1号位
    center_servo.slow_run_to(228 / 2);
    delay(500);                //1200
    servo_3.quick_down(1550);  //1050
    claw_31.grab();
    sucker_32.suck();
    delay(1000);
    servo_3.quick_up(2100);  //2650
    servo_3.stop(96);

    //0号吸盘吸2号位箱子且1号吸盘吸3号位箱子
    center_servo.slow_run_to(178 / 2);
    delay(500);
    servo_1.quick_down(1200);  //1050
    sucker_11.suck();
    sucker_12.suck();
    delay(1000);
    servo_1.quick_up(2100);  //2650
    servo_1.stop(96);

    //2号爪子抓4号位且3号爪子抓5号位
    center_servo.accelerate_run_to(132 / 2);
    delay(500);
    servo_2.quick_down(1700);  //1050
    claw_21.grab();
    claw_22.grab();
    delay(1000);
    servo_2.quick_up(2100);  //2650
    servo_2.stop(96);
}


void take() {
    switch (index) {
        case 0:
            take_1();
            break;

        case 1:
            take_2();
            break;

        case 2:
            take_3();
            break;

        case 3:
            take_4();
            break;

        case 4:
            take_5();
            break;

        case 5:
            take_6();
            break;

        case 6:
            take_7();
            break;

        case 7:
            take_8();
            break;

        case 8:
            take_9();
            break;

        case 9:
            take_10();
            break;

        case 10:
            take_11();
            break;

        case 11:
            take_12();
            break;

        case 12:
            take_13();
            break;

        case 13:
            take_14();
            break;

        case 14:
            take_15();
            break;

        case 15:
            take_16();
            break;

        case 16:
            take_17();
            break;

        case 17:
            take_18();
            break;

        case 18:
            take_19();
            break;

        case 19:
            take_20();
            break;
    }
}


void test() {
    initiate();
    //  Serial_receive();
    minimal_index();
    to_take();
    take();
    to_put();
    put();
}



void setup() {
    Serial.begin(9600);
    softSerial.begin(9600);
    // 修正脉冲宽度
    pinMode(motor_neg_pin, OUTPUT);
    pinMode(motor_pos_pin, OUTPUT);

    pinMode(sucker_11_pin, OUTPUT);
    pinMode(sucker_12_pin, OUTPUT);
    pinMode(sucker_32_pin, OUTPUT);

    pinMode(center_servo_relay_pin, OUTPUT);
    center_servo.attach(center_servo_pin, 500, 2500);

    claw_31.attach(claw_31_pin, 500, 2500);
    claw_21.attach(claw_21_pin, 500, 2500);
    claw_22.attach(claw_22_pin, 500, 2500);

    servo_1.attach(servo_1_pin, 500, 2500);
    servo_2.attach(servo_2_pin, 500, 2500);
    servo_3.attach(servo_3_pin, 500, 2500);
}

void loop() {
    test();
    exit(0);
}
