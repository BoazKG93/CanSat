#ifndef FUNCTIONS
#define FUNCTIONS

#include "Adafruit_Sensor.h"
#include "Adafruit_BMP280.h"
#include "Servo.h"
//Defining global vars
extern float prevAltitude;
extern int i; //timer
extern int eject;
extern int position;

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
int ejection(float prevAltitude, float currentAltitude); //TODO: Implement Ejection
//Connect the sensors
void connect();
//Get data
void getGyroData(data* rawData);
void getAnalogTemp(data* rawData, const int pin, int position);
void getBMEData(data* rawData);
//Rotate the engine
void rotateServo(int deg);
//Send the data to the receiver on the ground
void sendToGround(const char* msg);
//Read the sensors
void readSensors();

#endif 



