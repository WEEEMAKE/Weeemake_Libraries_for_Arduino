#include "WeRelay.h"

WeRelay::WeRelay(uint8_t port)
{
    _WeRelay.reset(port);
	
}

void WeRelay::reset(uint8_t port)
{	
	_WeRelay.reset(port);	
}

void WeRelay::openNC(void)
{
  setNC(true);
}

void WeRelay::closeNC(void)
{
  setNC(false);
}

void WeRelay::setNC(bool isOn)
{
    if(_WeRelay.reset())return;
    _WeRelay.write_byte(0x02); 
    _WeRelay.reset();
    _WeRelay.write_byte(isOn);
}
