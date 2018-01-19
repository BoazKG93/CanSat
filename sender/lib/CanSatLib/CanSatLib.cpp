#include "CanSatLib.h"

int newDataFromPC = 0;
Adafruit_BMP280 bme;

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


int getSignalFromPC() { 
  if(Serial.available() > 0) {
    int x = Serial.read();
	    if(x == 1) {
	    	newDataFromPC = 1;
	    	return 1;
	    }
    }
}

void replyToPC(char* string) {
  if (newDataFromPC) {
    newDataFromPC = 0;
    Serial.print("<");
    Serial.print(string);
    Serial.println(">");
  }
}







