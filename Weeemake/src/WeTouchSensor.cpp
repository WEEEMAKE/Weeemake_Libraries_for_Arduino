#include "WeTouchSensor.h"

WeTouchSensor::WeTouchSensor(uint8_t port)
{
  _WeTouchSensor.reset(port);
}
void WeTouchSensor::reset(uint8_t port)
{
	_WeTouchSensor.reset(port);
}

void WeTouchSensor::setMode(uint8_t mode)
{
	if(_WeTouchSensor.reset()!=0)
       return ;
    _WeTouchSensor.write_byte(0x03);
    if(_WeTouchSensor.reset()!=0)
       return ;
	_WeTouchSensor.write_byte(mode);

}

uint8_t WeTouchSensor::touched(void)
{
  if(_WeTouchSensor.reset()!=0)
    return 0;
  _WeTouchSensor.write_byte(0x02);
  _WeTouchSensor.respond();
  _Sensor1=_WeTouchSensor.read_byte();
  return _Sensor1;
}



