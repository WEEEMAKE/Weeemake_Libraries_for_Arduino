#include "WePIRSensor.h"


WePIRSensor::WePIRSensor(uint8_t port)
{
   _WePIRSensor.reset(port);
}
void WePIRSensor::reset(uint8_t port)
{
   _WePIRSensor.reset(port);
}

uint8_t WePIRSensor::readSensor(void)
{
   if(_WePIRSensor.reset()!=0)
	return 0;
   _WePIRSensor.write_byte(0x02);
   _WePIRSensor.respond();
   _Sensor=_WePIRSensor.read_byte();
   return _Sensor;
}




