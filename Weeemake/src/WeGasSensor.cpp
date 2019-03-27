#include "WeGasSensor.h"


WeGasSensor::WeGasSensor(uint8_t port)
{
  _WeGasSensor.reset(port);
}
void WeGasSensor::reset(uint8_t port)
{
	_WeGasSensor.reset(port);
}
void WeGasSensor::CloseLED(void)
{
	if(_WeGasSensor.reset()!=0)
       return ;
    _WeGasSensor.write_byte(0x03);
    if(_WeGasSensor.reset()!=0)
       return ;
	_WeGasSensor.write_byte(0x00);
}
void WeGasSensor::OpenLED(void)
{
	if(_WeGasSensor.reset()!=0)
       return ;
    _WeGasSensor.write_byte(0x03);
    if(_WeGasSensor.reset()!=0)
       return ;
	_WeGasSensor.write_byte(0x01);
}



uint8_t WeGasSensor::readAnalog(void)
{
  if(_WeGasSensor.reset()!=0)
    return 0;
  _WeGasSensor.write_byte(0x02);
  _WeGasSensor.respond();
  _Sensor1=_WeGasSensor.read_byte();

  return _Sensor1;
}



