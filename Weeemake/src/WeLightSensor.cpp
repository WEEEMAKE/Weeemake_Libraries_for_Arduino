#include "WeLightSensor.h"

WeLightSensor::WeLightSensor(uint8_t port)
{
  _Sensorpin=port;
}

int16_t WeLightSensor::read(void)
{
   return(analogRead(_Sensorpin));
}

WeLightSensor_RJ::WeLightSensor_RJ(uint8_t port)
{
  reset(port);
}
void WeLightSensor_RJ::reset(uint8_t port)
{
	_WeLightSensor_RJ.reset(port);
}

uint16_t WeLightSensor_RJ::read(void)
{
  if(_WeLightSensor_RJ.reset()!=0)
    return 0;
  _WeLightSensor_RJ.write_byte(0x02);
  _WeLightSensor_RJ.respond();
  uint8_t value = _WeLightSensor_RJ.read_byte();
  return uint16_t(value * 1023.0 / 255.0);
}



