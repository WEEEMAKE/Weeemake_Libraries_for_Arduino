#include "WeSoundSensor.h"



WeSoundSensor::WeSoundSensor(uint8_t port)
{
  _Sensorpin=port;
}

uint16_t WeSoundSensor::read(void)
{
   return(analogRead(_Sensorpin));
}

WeSoundSensor_RJ::WeSoundSensor_RJ(uint8_t port)
{
  reset(port);
}
void WeSoundSensor_RJ::reset(uint8_t port)
{
	_WeSoundSensor_RJ.reset(port);
}

uint16_t WeSoundSensor_RJ::read(void)
{
  if(_WeSoundSensor_RJ.reset()!=0)
    return 0;
  _WeSoundSensor_RJ.write_byte(0x02);
  _WeSoundSensor_RJ.respond();
  uint8_t value = _WeSoundSensor_RJ.read_byte();
  return uint16_t(value * 1023.0 / 255.0);
}



