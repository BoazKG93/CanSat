#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Servo.h"
#include "CanSatLib.h"
Servo myservo;

unsigned long StartTime = 0;
unsigned long CurrentTime = 0;
unsigned long ElapsedTime;
float prevAltitude;
int i = 1;
int online = 0;
int go = 0;
int eject = 0;
int position = 0;

void readSensors() {
    struct data* rawData = (data*)malloc(sizeof(data));
    CurrentTime = millis();
    ElapsedTime = (CurrentTime - StartTime);
    getGyroData(rawData);
    getAnalogTemp(rawData, 0, Inner);
    getAnalogTemp(rawData, 1, Outer);
    getBMEData(rawData);
    if(i==1||i%2 == 0) { //one second has passed, update prevAltitude
        prevAltitude = rawData->altitude;
    } else if(!eject) {
        eject = ejection(prevAltitude, rawData->altitude);
    }
    //Send data in csv form:   
    Serial.print("<");
    Serial.print(ElapsedTime); // divide by 512 is approx = half-seconds
    Serial.print(","); Serial.print(rawData->innerAnalogTemp);
    Serial.print(","); Serial.print(rawData->outerAnalogTemp);
    Serial.print(","); Serial.print(rawData->pressure);
    Serial.print(","); Serial.print(rawData->altitude);
    Serial.print(","); Serial.print(rawData->AccX);
    Serial.print(","); Serial.print(rawData->AccY);
    Serial.print(","); Serial.print(rawData->AccZ);
    Serial.print(","); Serial.print(rawData->innerDigitalTemp);
    Serial.print(","); Serial.print(position);
    Serial.println(">");
     //free the data 
     free(rawData); 
}

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
            digitalWrite(13, HIGH);
            online = 1; //Going online!
            connect();
            myservo.attach(11);
            Serial.print("<Satallite is ready>");
            delay(200);
            position = 20;
            myservo.write(position);
            Serial.print("<Example sensor read:>");
            delay(100);
            readSensors();
        }
    } else if(Serial.available() > 0 && !go && online) {
        char x = Serial.read();
        int y = x;
        if(y == 49) {
            digitalWrite(12, HIGH);
            go = 1; //Going online!
            Serial.print("<Satallite has been launched>");
            StartTime = millis();
        }
    } else if(online && go) {
        if((eject && i>6) || i > 10) { //100s time..
            //TODO: Implement motor signal to eject
            position = 180;
            myservo.write(position);
        }

        readSensors();
        i++;
        
    }
    delay(500);
    
}



