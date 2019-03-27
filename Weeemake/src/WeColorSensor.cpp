#include "WeColorSensor.h"


WeColorSensor::WeColorSensor(uint8_t port)
:wb_flag(false)
{
  reset(port);
}
void WeColorSensor::reset(uint8_t port)
{
  _WeColorSensor.reset(port);
}
void WeColorSensor::readColorData(void)
{
	uint8_t ColorData[8] = {0};
	if(_WeColorSensor.reset()!=0)
		return ;
	_WeColorSensor.write_byte(0x02);
	_WeColorSensor.respond();
	for(int i=0;i<8;i++)
    {
       ColorData[i]=_WeColorSensor.read_byte();
    }
	Redvalue   = (uint16_t)ColorData[1] << 8 | ColorData[0];
    Greenvalue = (uint16_t)ColorData[3] << 8 | ColorData[2];
    Bluevalue  = (uint16_t)ColorData[5] << 8 | ColorData[4];
    Colorvalue = (uint16_t)ColorData[7] << 8 | ColorData[6];
}
uint16_t WeColorSensor::showRedData(void)
{
  return Redvalue;
}
uint16_t WeColorSensor::showGreenData(void)
{
  return wb_flag ? Greenvalue : (Greenvalue / 2.2);
}
uint16_t WeColorSensor::showBlueData(void)
{
  return wb_flag ? Bluevalue : (Bluevalue / 1.2);
}
uint16_t WeColorSensor::showColorData(void)
{
  return Colorvalue;
}

void WeColorSensor::whitebalance(void)
{
    if(_WeColorSensor.reset()!=0)
       return ;
    _WeColorSensor.write_byte(0x04);
    delayMicroseconds(3000);
    wb_flag = true;
}

void WeColorSensor::turnOnLight(void)
{
    setLight(true);
}
void WeColorSensor::turnOffLight(void)
{
    setLight(false);
}

void WeColorSensor::setLight(bool isOn)
{
	if(_WeColorSensor.reset())return;
	_WeColorSensor.write_byte(0x03);
	if(_WeColorSensor.reset())return;
	_WeColorSensor.write_byte(isOn);
}

uint16_t WeColorSensor::readValue(uint8_t type)
{
	readColorData();
	switch(type){
		case 1: return showRedData();
		case 2: return showGreenData();
		case 3: return showBlueData();
	}
	return showColorData();
}
