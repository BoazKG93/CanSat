#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "CanSatLib.h"

unsigned long curMillis;
unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

int online = 0;

//=============

void setup() {
  Serial.begin(9600);
}

//=============

void loop() {
  curMillis = millis();
  if(!online) {
    //Wait for activation signal from PC
    online = getSignalFromPC();
    connect();
  } else {
    //Reply that systems are go
    //TODO: Add a real check of the sensors
    replyToPC("Satallite is ready");
    //Start sending data to the PC
    //Get data:
    struct data* rawData = (data*)malloc(sizeof(data));
    getGyroData(rawData);
    getAnalogTemp(rawData, 0, Inner);
    getAnalogTemp(rawData, 1, Outer);
    getBMEData(rawData);
    //TODO: Eject the satallite when data reachs critirium
    //Send data in csv form:
    Serial.print("<");
    Serial.print(curMillis >> 9); // divide by 512 is approx = half-seconds
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
    delay(1000);
  }
}
