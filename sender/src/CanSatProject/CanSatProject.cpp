#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "CanSatLib.h"

int online = 0;
int go = 0;

//=============

void setup() {
  Serial.begin(9600);
}

//=============

void loop() {
    if(Serial.available() > 0 && !online) {
        char x = Serial.read();
        int y = x;
        if(y == 49) {
            online = 1; //Going online!
            connect();
            sendToGround("Satallite is ready");
            delay(200);
            sendToGround("Example sensor read:");
            delay(100);
            readSensors();
        }
    } else if(Serial.available() > 0 && !go && online) {
        char x = Serial.read();
        int y = x;
        if(y == 49) {
            go = 1; //Going online!
            sendToGround("Satallite has been launched");
        }
    } else if(online && go) {
        if((eject && i>=6) || i >= 9) { //3s and 4.5s time..
            position = 180;
            rotateServo(position);
        }

        readSensors();
        i++;
        
    }
    delay(500);
    
}



