#include "WeJoystick.h"


WeJoystick::WeJoystick(uint8_t port)
{
  _WeJoystick.reset(port);
}
void WeJoystick::reset(uint8_t port)
{
	_WeJoystick.reset(port);
}


void WeJoystick::readData(void)
{
  if(_WeJoystick.reset()!=0)
    return ;
  _WeJoystick.write_byte(0x02);
  _WeJoystick.respond();
  _Sensor1=_WeJoystick.read_byte();
  _Sensor2=_WeJoystick.read_byte();
  _Sensor3=_WeJoystick.read_byte();

  _Sensor1=map(_Sensor1,0,255,255,0);
}

uint8_t WeJoystick::showX(void)
{
  return _Sensor1;
}
uint8_t WeJoystick::showY(void)
{
  return _Sensor2;
}
uint8_t WeJoystick::showKey(void)
{
  return _Sensor3;
}

uint8_t WeJoystick::readValue(uint8_t axis)
{
  readData();
  switch(axis){
    case 0: return _Sensor1;
    case 1: return _Sensor2;
  }
  return _Sensor3;
}





