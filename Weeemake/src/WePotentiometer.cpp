#include "WePotentiometer.h"


WePotentiometer::WePotentiometer(uint8_t port)
{
  _WePotentiometer.reset(port);
}
void WePotentiometer::reset(uint8_t port)
{
	_WePotentiometer.reset(port);
}
void WePotentiometer::CloseLED(void)
{
	if(_WePotentiometer.reset()!=0)
       return ;
    _WePotentiometer.write_byte(0x03);
    if(_WePotentiometer.reset()!=0)
       return ;
	_WePotentiometer.write_byte(0x00);
}
void WePotentiometer::OpenLED(void)
{
	if(_WePotentiometer.reset()!=0)
       return ;
    _WePotentiometer.write_byte(0x03);
    if(_WePotentiometer.reset()!=0)
       return ;
	_WePotentiometer.write_byte(0x01);
}



uint8_t WePotentiometer::readAnalog(void)
{
  if(_WePotentiometer.reset()!=0)
    return 0;
  _WePotentiometer.write_byte(0x02);
  _WePotentiometer.respond();
  _Sensor1=_WePotentiometer.read_byte();

  return _Sensor1;
}



