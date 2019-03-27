#include "WeFunnyTouchSensor.h"

WeFunnyTouchSensor::WeFunnyTouchSensor(uint8_t port)
{
  _WeFunnyTouchSensor.reset(port);
}
void WeFunnyTouchSensor::reset(uint8_t port)
{
	_WeFunnyTouchSensor.reset(port);
}

uint8_t WeFunnyTouchSensor::readValue(void)
{
  if(_WeFunnyTouchSensor.reset()!=0)
    return 0;
  _WeFunnyTouchSensor.write_byte(0x02);
  _WeFunnyTouchSensor.respond();
  _Sensor1=_WeFunnyTouchSensor.read_byte();

  return _Sensor1;
}



