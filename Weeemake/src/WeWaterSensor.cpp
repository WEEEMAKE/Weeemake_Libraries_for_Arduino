#include "WeWaterSensor.h"


WeWaterSensor::WeWaterSensor(uint8_t port)
{
  _WeWaterSensor.reset(port);
}
void WeWaterSensor::reset(uint8_t port)
{
	_WeWaterSensor.reset(port);
}


uint8_t WeWaterSensor::readAnalog(void)
{
  if(_WeWaterSensor.reset()!=0)
    return 0;
  _WeWaterSensor.write_byte(0x02);
  _WeWaterSensor.respond();
  _Sensor1=_WeWaterSensor.read_byte();

  return _Sensor1;
}



