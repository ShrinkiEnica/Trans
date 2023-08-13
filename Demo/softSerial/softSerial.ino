#include <SoftwareSerial.h>
SoftwareSerial softSerial(12, 13); // RX, TX
void setup()
{
  softSerial.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  digitalWrite(53, LOW);
  if (softSerial.available())
  {
    // 至少得delay 200 ms
    // 在openmv中最好也sleep_ms 10
    delay(200);
    if (softSerial.read() == 's')
    {
      Serial.print("fuck");
    }
  }
}
