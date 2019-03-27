#include "WeBarometerSensor.h"

WeBarometerSensor::WeBarometerSensor(uint8_t port)
{
   _WeBarometerSensor.reset(port);
}
void WeBarometerSensor::reset(uint8_t port)
{
   _WeBarometerSensor.reset(port);
}

float WeBarometerSensor::readHeight(void)
{
   if(_WeBarometerSensor.reset()!=0)
		return 0;
	_WeBarometerSensor.write_byte(0x02);
	_WeBarometerSensor.respond();
     BarometerData[0]=_WeBarometerSensor.read_byte();
	BarometerData[1]=_WeBarometerSensor.read_byte();
	BarometerData[2]=_WeBarometerSensor.read_byte();
	BarometerData[3]=_WeBarometerSensor.read_byte();
	height=(int32_t)BarometerData[0]+((int32_t)BarometerData[1]<<8)+((int32_t)BarometerData[2]<<16)+((int32_t)BarometerData[3]<<24);
	height=height/1;
	return height;
}

float WeBarometerSensor::readPressure(void)
{
   if(_WeBarometerSensor.reset()!=0)
		return 0;
	_WeBarometerSensor.write_byte(0x03);
	_WeBarometerSensor.respond();
     BarometerData[0]=_WeBarometerSensor.read_byte();
	BarometerData[1]=_WeBarometerSensor.read_byte();
	BarometerData[2]=_WeBarometerSensor.read_byte();
	BarometerData[3]=_WeBarometerSensor.read_byte();
	height=(uint32_t)BarometerData[0]+((uint32_t)BarometerData[1]<<8)+((uint32_t)BarometerData[2]<<16)+((uint32_t)BarometerData[3]<<24);
	height=height/100;
	return height;
}

float WeBarometerSensor::readTemp(void)
{
   if(_WeBarometerSensor.reset()!=0)
		return 0;
	_WeBarometerSensor.write_byte(0x04);
	_WeBarometerSensor.respond();
     BarometerData[0]=_WeBarometerSensor.read_byte();
	BarometerData[1]=_WeBarometerSensor.read_byte();
	BarometerData[2]=_WeBarometerSensor.read_byte();
	BarometerData[3]=_WeBarometerSensor.read_byte();
	height=(uint32_t)BarometerData[0]+((uint32_t)BarometerData[1]<<8)+((uint32_t)BarometerData[2]<<16)+((uint32_t)BarometerData[3]<<24);
	height=height/100;
	return height;
}
float WeBarometerSensor::readRelativeHeight(void)
{
   if(_WeBarometerSensor.reset()!=0)
		return 0;
	_WeBarometerSensor.write_byte(0x02);
	_WeBarometerSensor.respond();
     BarometerData[0]=_WeBarometerSensor.read_byte();
	BarometerData[1]=_WeBarometerSensor.read_byte();
	BarometerData[2]=_WeBarometerSensor.read_byte();
	BarometerData[3]=_WeBarometerSensor.read_byte();
	height=(int32_t)BarometerData[0]+((int32_t)BarometerData[1]<<8)+((int32_t)BarometerData[2]<<16)+((int32_t)BarometerData[3]<<24);
	height=height/100;
	return height;
}

void WeBarometerSensor::setOrigin(void)
{
   if(_WeBarometerSensor.reset()!=0)
		return ;
	_WeBarometerSensor.write_byte(0x05);
	delay(200);
}




