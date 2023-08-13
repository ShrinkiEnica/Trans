#include <Servo.h>

class Center_servo {
private:
  Servo center_servo;
  int pin;
  int angle;
  int relay_pin;

public:
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
      delay(60);  //40
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
  void run_with_accelerate(int run_to_angle) {
    int delta_angle = run_to_angle - this->angle;
    int begin_angle = this->angle;
    run_to(begin_angle + (int)(0.3 * delta_angle));
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
