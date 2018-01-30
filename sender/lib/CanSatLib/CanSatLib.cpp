#include "CanSatLib.h"

Adafruit_BMP280 bme;
Servo servo;

float prevAltitude;
int i = 0;
int eject = 0;
int position = 0;

void connect() {
  	//Connect bme
  	bme.begin();
  	//Connect to MPU 6050
  	const int addr = 0x68;
  	const byte ACCEL_CONFIG = 0x1C;
  	const byte GYRO_CONFIG = 0x1B;
  	const byte PWR_MGMT_1 = 0x6B;
	Wire.begin();
	Wire.beginTransmission(addr);
	Wire.write(PWR_MGMT_1);
	Wire.write(0);
	Wire.endTransmission();
	Wire.beginTransmission(addr);
	Wire.write(ACCEL_CONFIG);
	Wire.write(0x10);
	Wire.endTransmission();
	Wire.beginTransmission(addr);
	Wire.write(GYRO_CONFIG);
	Wire.write(0x08);
	Wire.endTransmission();
	servo.attach(11);
}

void getGyroData(data* rawData) {
  
  	const int addr = 0x68;
  	const byte ACCEL_XOUT_H = 0x3B;
	Wire.beginTransmission(addr);
	Wire.write(ACCEL_XOUT_H);
	Wire.endTransmission();
	Wire.requestFrom(addr, 14);

	rawData->AccX = Wire.read() << 8 | Wire.read();
	rawData->AccY = Wire.read() << 8 | Wire.read();
	rawData->AccZ = Wire.read() << 8 | Wire.read();
	rawData->innerDigitalTemp = Wire.read() << 8 | Wire.read();
	rawData->GyroX = Wire.read() << 8 | Wire.read();
	rawData->GyroY = Wire.read() << 8 | Wire.read();
	rawData->GyroZ = Wire.read() << 8 | Wire.read();
  	rawData->AccX = rawData->AccX/4096;
  	rawData->AccY = rawData->AccY/4096;
  	rawData->AccZ = rawData->AccZ/4096;
  	rawData->innerDigitalTemp = rawData->innerDigitalTemp/340 + 36.53;
  	rawData->GyroX = rawData->GyroX/65.5;
  	rawData->GyroY = rawData->GyroY/65.5;
  	rawData->GyroZ = rawData->GyroZ/65.5;


}



void getAnalogTemp(data* rawData, const int pin, int position) {
	if(position == 0) {
		rawData->outerAnalogTemp = analogRead(pin);
    	rawData->outerAnalogTemp = rawData->outerAnalogTemp*5000/1023 * 1/10;
	}
	if(position == 1) {
		rawData->innerAnalogTemp = analogRead(pin);
   		rawData->innerAnalogTemp = rawData->innerAnalogTemp*5000/1023 * 1/10;
	}
	
}

void getBMEData(data* rawData) {
	rawData->bmeTemp = bme.readTemperature();
	rawData->pressure = bme.readPressure()/100;
	rawData->altitude = bme.readAltitude(1013.25);
}


int ejection(float prevAltitude, float currentAltitude) {
	float diff = currentAltitude - prevAltitude;
	if(diff < -0.8) { //1 for 1cm or 1m fall?
		return 1;
	} else {
		return 0;
	}
}

void sendToGround(const char* msg) {
	char* string = (char*)malloc(strlen(msg)+2);
	memcpy(&string[0], "<", 1);
	memcpy(&string[1], msg, strlen(msg));
	memcpy(&string[strlen(msg)+1], ">", 1);
	string[strlen(msg)+2] = '\0';
	Serial.print(string);
	free(string);
}

void rotateServo(int deg) {
	servo.write(deg);
}

void readSensors() {
    struct data* rawData = (data*)malloc(sizeof(data));

    //Retrive data from sensors
    getGyroData(rawData);
    getAnalogTemp(rawData, 1, Inner);
    getAnalogTemp(rawData, 0, Outer);
    getBMEData(rawData);

    //Calculate ejection
    if(i%2 == 0) { //one second has passed, update prevAltitude
    	if(prevAltitude != 0) {
    		eject = ejection(prevAltitude, rawData->altitude);	
    	}
        prevAltitude = rawData->altitude;
    } else if(!eject) {
    	eject = ejection(prevAltitude, rawData->altitude);
    }
    
    float timeF = ((float)i*500.0)/1000.0; //Calculating time - i*500ms divided by 1000 will give seconds
    //Converting floats to string due to Arduino lack of support in sprintf
    char time[10], innerDigitalTemp[10], outerAnalogTemp[10], innerAnalogTemp[10], pressure[10], altitude[10], AccZ[10], AccY[10], AccX[10];
    dtostrf(timeF, 1, 1, time);
    dtostrf(rawData->innerAnalogTemp, 3, 2, innerAnalogTemp);
    dtostrf(rawData->outerAnalogTemp, 3, 2, outerAnalogTemp);
    dtostrf(rawData->pressure, 3, 2, pressure);
    dtostrf(rawData->altitude, 3, 2, altitude);
    dtostrf(rawData->AccX, 3, 2, AccX);
    dtostrf(rawData->AccY, 3, 2, AccY);
    dtostrf(rawData->AccZ, 3, 2, AccZ);
    dtostrf(rawData->innerDigitalTemp, 3, 3, innerDigitalTemp);

    //Calcualting total length
    int len = snprintf(NULL, 0, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d", time , innerAnalogTemp, outerAnalogTemp, pressure, altitude, AccX, AccY, AccZ, innerDigitalTemp, position);
    char* buffer = (char*)malloc(sizeof(char)*len+1); //+1 for trailing 0

    //Saving to the buffer and sending to ground
    sprintf(buffer, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%d", time, innerAnalogTemp, outerAnalogTemp, pressure, altitude, AccX, AccY, AccZ, innerDigitalTemp, position);
    sendToGround(buffer);

    //Free the data
    free(buffer);
    free(rawData); 
}
