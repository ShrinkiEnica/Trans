#include <SoftwareSerial.h>
int i = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  i++;
  Serial.print(i);
  delay(10);
  if(i == 20)
  {
    exit(0);
  }
}
