#include "WeUVSensor.h"


WeUVSensor::WeUVSensor(uint8_t port)
{
  _WeUVSensor.reset(port);
}
void WeUVSensor::reset(uint8_t port)
{
  _WeUVSensor.reset(port);
}


uint8_t WeUVSensor::readAnalog(void)
{
  if(_WeUVSensor.reset()!=0)
    return 0;
  _WeUVSensor.write_byte(0x02);
  _WeUVSensor.respond();
  _Sensor1=_WeUVSensor.read_byte();

  return _Sensor1;
}

uint8_t WeUVSensor::readIndex(void)
{
  if(_WeUVSensor.reset()!=0)
    return 0;
  _WeUVSensor.write_byte(0x03);
  _WeUVSensor.respond();
  _Sensor1=_WeUVSensor.read_byte();

  return _Sensor1;
}


