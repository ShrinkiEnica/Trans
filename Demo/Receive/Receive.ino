#include <SoftwareSerial.h>

int rxPin = 10;
int txPin = 11;
int i = 0;
SoftwareSerial mySerial= SoftwareSerial(rxPin, txPin);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mySerial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("receive");
  delay(50);
  Serial.println(mySerial.read());
  i++;
  if(i == 100)
  {
    exit(0);
  }
}
