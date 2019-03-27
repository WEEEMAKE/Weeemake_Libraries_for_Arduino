#include "WeSlidingPotentiomter.h"


WeSlidingPotentiomter::WeSlidingPotentiomter(uint8_t port)
{
  _WeSlidingPotentiomter.reset(port);
}
void WeSlidingPotentiomter::reset(uint8_t port)
{
	_WeSlidingPotentiomter.reset(port);
}


uint8_t WeSlidingPotentiomter::readAnalog(void)
{
  if(_WeSlidingPotentiomter.reset()!=0)
    return 0;
  _WeSlidingPotentiomter.write_byte(0x02);
  _WeSlidingPotentiomter.respond();
  _Sensor1=_WeSlidingPotentiomter.read_byte();

  return _Sensor1;
}



