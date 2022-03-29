#include "WeGestureSensor.h"


WeGestureSensor::WeGestureSensor(uint8_t port)
{
  _WeGestureSensor.reset(port);
}
void WeGestureSensor::reset(uint8_t port)
{
	_WeGestureSensor.reset(port);
}


uint8_t WeGestureSensor::read(void)
{
  if(_WeGestureSensor.reset()!=0)
    return 0;
  _WeGestureSensor.write_byte(0x02);
  _WeGestureSensor.respond();
  _Sensor1=_WeGestureSensor.read_byte();
  delay(10);
  return _Sensor1;
}

void WeGestureSensor::position(void)
{
	if(_WeGestureSensor.reset()!=0)
		return ;
	_WeGestureSensor.write_byte(0x03);
	_WeGestureSensor.respond();
	uint8_t x_high=_WeGestureSensor.read_byte();
	uint8_t x_low=_WeGestureSensor.read_byte();
	uint8_t y_high=_WeGestureSensor.read_byte();
	uint8_t y_low=_WeGestureSensor.read_byte();
	objectSize=_WeGestureSensor.read_byte();
    centerX=x_high<<4|x_low>>4;
	centerY=y_high<<4|y_low>>4;
	delay(10);
}


