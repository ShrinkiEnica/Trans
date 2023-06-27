int CCD_CLK = 9;
int CCD_SI = 8;
int ADC_pin = A3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(4800);
  pinMode(CCD_CLK, OUTPUT);
  pinMode(CCD_SI, OUTPUT);
  pinMode(ADC_pin, INPUT);
}

void loop() {
  int i = 0;
  long int b = 0;
  long int CCD_ADV[128];

  digitalWrite(CCD_CLK, HIGH);
  digitalWrite(CCD_SI, LOW);
  delayMicroseconds(1);
  digitalWrite(CCD_SI, HIGH);
  digitalWrite(CCD_CLK, LOW);
  delayMicroseconds(1);
  digitalWrite(CCD_CLK, HIGH);
  digitalWrite(CCD_SI, LOW);
  delayMicroseconds(1);
  for (i = 0; i < 128; i++)
  {
    digitalWrite(CCD_CLK, LOW);
    delayMicroseconds(1);
    b = analogRead(ADC_pin);
    delayMicroseconds(1);
    CCD_ADV[i] = b / 4;  //除以4可将十位ADC值转化为八位
    delayMicroseconds(1);
    digitalWrite(CCD_CLK, HIGH);
    delayMicroseconds(1);
  }
  for (i = 0;i < 128;i++)
  {
    Serial.println(CCD_ADV[i]);
    delay(1);
  }
  exit(0);
}

