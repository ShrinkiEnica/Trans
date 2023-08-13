#include <SoftwareSerial.h>
#include "class.h"
SoftwareSerial mySerial(12,13);

int device_use_num[6] = {0,0,0,0,0,0};
void setup() {
    Serial.begin(9600);
    mySerial.begin(9600);
}

void loop() {

    while(1){
        if (mySerial.available()){
            int num = mySerial.read() - '0';
            switch (num){
                case 0:
                    if (device_use_num[0] == 0)
                        sucker_11.suck();
                    if (device_use_num[0] == 1)
                        sucker_11.exhale();
                case 1:
                    if (device_use_num[0] == 0)
                        sucker_12.suck();
                    if (device_use_num[0] == 1)
                        sucker_12.suck();
                case 2:
                    if (device_use_num[0] == 0)
                        claw_21.grab();
                    if (device_use_num[0] == 1)
                        claw_21.release();
                case 3:
                    if (device_use_num[0] == 0)
                        claw_22.grab();
                    if (device_use_num[0] == 1)
                        claw_22.release();
                case 4:
                    if (device_use_num[0] == 0)
                        claw_31.grab();
                    if (device_use_num[0] == 1)
                        claw_31.release();
                case 5:
                    if (device_use_num[0] == 0)
                        sucker_32.suck();
                    if (device_use_num[0] == 1)
                        sucker_32.suck();
            }
        }
    }
}
}
