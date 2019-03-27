#include "WePotentiomter.h"


WePotentiomter::WePotentiomter(uint8_t port)
{
  _WePotentiomter.reset(port);
}
void WePotentiomter::reset(uint8_t port)
{
	_WePotentiomter.reset(port);
}
void WePotentiomter::CloseLED(void)
{
	if(_WePotentiomter.reset()!=0)
       return ;
    _WePotentiomter.write_byte(0x03);
    if(_WePotentiomter.reset()!=0)
       return ;
	_WePotentiomter.write_byte(0x00);
}
void WePotentiomter::OpenLED(void)
{
	if(_WePotentiomter.reset()!=0)
       return ;
    _WePotentiomter.write_byte(0x03);
    if(_WePotentiomter.reset()!=0)
       return ;
	_WePotentiomter.write_byte(0x01);
}



uint8_t WePotentiomter::readAnalog(void)
{
  if(_WePotentiomter.reset()!=0)
    return 0;
  _WePotentiomter.write_byte(0x02);
  _WePotentiomter.respond();
  _Sensor1=_WePotentiomter.read_byte();

  return _Sensor1;
}



