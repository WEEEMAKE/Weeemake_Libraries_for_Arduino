#include "WeTiltSwitch.h"


WeTiltSwitch::WeTiltSwitch(uint8_t port)
{
   _WeTiltSwitch.reset(port);
}
void WeTiltSwitch::reset(uint8_t port)
{
   _WeTiltSwitch.reset(port);
}

uint8_t WeTiltSwitch::readSensor(void)
{
   if(_WeTiltSwitch.reset()!=0)
	return 0;
   _WeTiltSwitch.write_byte(0x02);
   _WeTiltSwitch.respond();
   _Sensor=_WeTiltSwitch.read_byte();
   return _Sensor;
}

bool WeTiltSwitch::readSensor(uint8_t index)
{
	uint8_t value = readSensor();
	switch(index){
		case 1: return value == 2;
		case 2: return value == 1;
	}
	return value != 0;
}


