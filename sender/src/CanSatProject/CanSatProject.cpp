#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "CanSatLib.h"

unsigned long StartTime = 0;
unsigned long CurrentTime = 0;
unsigned long ElapsedTime;
float prevAltitude;
int i = 1;
int online = 0;
int go = 0;
int eject = 0;

void readSensors() {
    CurrentTime = millis();
    ElapsedTime = (CurrentTime - StartTime);
    struct data* rawData = (data*)malloc(sizeof(data));
    getGyroData(rawData);
    getAnalogTemp(rawData, 0, Inner);
    getAnalogTemp(rawData, 1, Outer);
    getBMEData(rawData);
    if(i==1||i%2 == 0) { //one second has passed, update prevAltitude
        prevAltitude = rawData->altitude;
    } else if(!eject) {
        eject = ejection(prevAltitude, rawData->altitude);
    }
    //TODO: Eject the satallite when data reachs critirium
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
    Serial.println(">");
    free(rawData); //free the data  
}

//=============

void setup() {
  Serial.begin(9600);
}

//=============

void loop() {
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
    if(Serial.available() > 0 && !online) {
        char x = Serial.read();
        int y = x;
        if(y == 49) {
            digitalWrite(13, HIGH);
            online = 1; //Going online!
            connect();
            Serial.print("<Satallite is ready>");
            Serial.print("<Example sensor read:>");
            readSensors();
        }
    } else if(Serial.available() > 0 && !go) {
        char x = Serial.read();
        int y = x;
        if(y == 49) {
            digitalWrite(12, HIGH);
            go = 1; //Going online!
            Serial.print("<Satallite has been launched>");
            StartTime = millis();
        }
    } else if(online && go) {
        if((eject && i>1) || i > 200) { //100s time..
            //TODO: Implement motor signal to eject
            digitalWrite(11, HIGH);
        }

        readSensors();

        i++;
    }
    delay(500);
}



