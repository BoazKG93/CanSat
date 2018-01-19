#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "CanSatLib.h"

void setup() {
	Serial.begin(9600);
	connect();
}

void loop() {
	struct data* rawData = (data*)malloc(sizeof(data));
	getGyroData(rawData);
	getAnalogTemp(rawData, 0, Inner);
	getAnalogTemp(rawData, 1, Outer);
  getBMEData(rawData);
	Serial.print("Inner temp: "); Serial.print(rawData->innerAnalogTemp);
  Serial.print(" Outer temp: "); Serial.print(rawData->outerAnalogTemp);
  Serial.print(" Pressure: "); Serial.print(rawData->pressure);
  Serial.print(" Altitude: "); Serial.print(rawData->altitude);
  Serial.print(" AccX: "); Serial.print(rawData->AccX);
  Serial.print(" AccY: "); Serial.print(rawData->AccY);
  Serial.print(" AccZ: "); Serial.print(rawData->AccZ);
  Serial.print(" Digital Temp: "); Serial.print(rawData->innerDigitalTemp);
  Serial.print("\n");

  	free(rawData);
	delay(1000);
}
