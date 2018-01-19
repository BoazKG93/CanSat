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


//Start systems
int launch();

//Eject the can
int ejection();

//Collect the data
void connect();

void getGyroData(data* rawData);

void getAnalogTemp(data* rawData, const int pin, int position);

void getBMEData(data* rawData);

//Save the data
void saveData();

#endif 



