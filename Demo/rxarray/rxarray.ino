//根据串口输入内容，进行判断，调用相应的函数
int i = 0;
void Fist(){
    Serial.println("石头");
}
 
void Two(){
    Serial.println("剪刀");
}
 
void Five(){
    Serial.println("布");
 
}
 
 
void setup() {
    //设定串口频率
    Serial.begin(9600);
}
 
 
void loop() {
  while (Serial.available()) {
    
    int inByte = Serial.read();
    //↑将获取到的内容，例如通过串口输入的是0，变量inByte值实际上为48（ASCII编码）
    //↓则需要转换为字符0，以便后面的程序判断，字符型是单引号，千万不要用成双引号
    char user = (char)inByte;
 
      if (user == '0') {
        Fist();
        i++;
        Serial.println(i);
      } else if (user == '2') {
        Two();
        i++;
        Serial.println(i);
      } else if (user == '5') {
        Five();
        i++;
        Serial.println(i);
      }
      else{
          Serial.println(user);
      }
      
    
    }
 
  }