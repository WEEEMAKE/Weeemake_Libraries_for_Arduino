#include "WeSlidingPotentiometer.h"


WeSlidingPotentiometer::WeSlidingPotentiometer(uint8_t port)
{
  _WeSlidingPotentiometer.reset(port);
}
void WeSlidingPotentiometer::reset(uint8_t port)
{
	_WeSlidingPotentiometer.reset(port);
}


uint8_t WeSlidingPotentiometer::readAnalog(void)
{
  if(_WeSlidingPotentiometer.reset()!=0)
    return 0;
  _WeSlidingPotentiometer.write_byte(0x02);
  _WeSlidingPotentiometer.respond();
  _Sensor1=_WeSlidingPotentiometer.read_byte();

  return _Sensor1;
}



