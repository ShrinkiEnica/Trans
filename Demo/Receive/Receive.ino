void setup() {
  Serial.begin(9600);
}

int device_use_sequence[6] = {};
int item_take_sequence[6] = {};
void loop() {
  if (Serial.available()){
    if (Serial.read() == 's'){
        for (int i = 0; i < 6; i++){
            device_use_sequence[i] = Serial.read() - '0';
        }
        for (int i = 0; i < 6; i++){
            item_take_sequence[i] = Serial.read() - '0';
        }
        for (int i = 0; i < 6;i++){
            Serial.write(device_use_sequence[i] + '0');
        }
        for (int i = 0; i < 6;i++){
            Serial.write(item_take_sequence[i] + '0');
        }
    }

  }
}
