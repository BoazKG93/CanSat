#ifndef FUNCTIONS
#define FUNCTIONS

#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"


enum Position {Outer = 0, Inner = 1};

typedef struct data {
  float innerDigitalTemp;
  float outerAnalogTemp;
  float innerAnalogTemp;
  float bmeTemp;
  float pressure;
  float altitude;
  float AccX;
  float AccY;
  float AccZ;
  float GyroX;
  float GyroY;
  float GyroZ;
} data;


//Eject the can
int ejection(); //TODO: Implement Ejection
//Connect the sensors
void connect();
//Get data
void getGyroData(data* rawData);
void getAnalogTemp(data* rawData, const int pin, int position);
void getBMEData(data* rawData);
//Get launch signal from PC
int getSignalFromPC();
//Replay to PC
void replyToPC(char* string);

#endif 



