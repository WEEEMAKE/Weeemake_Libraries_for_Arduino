#include "WeIRThermometerSensor.h"


WeIRThermometerSensor::WeIRThermometerSensor(uint8_t port)
{
  _WeIRThermometerSensor.reset(port);
}
void WeIRThermometerSensor::reset(uint8_t port)
{
	_WeIRThermometerSensor.reset(port);
}

float WeIRThermometerSensor::readAmbientTempC(void)
{
   if(_WeIRThermometerSensor.reset()!=0)
  	return -200;
  _WeIRThermometerSensor.write_byte(0x02);
  _WeIRThermometerSensor.respond();
  _Sensor1=_WeIRThermometerSensor.read_byte();
  _Sensor2=_WeIRThermometerSensor.read_byte();	
  _data=((uint16_t)_Sensor2 << 8 | _Sensor1)*0.02-273.15;
  return _data;
}
float WeIRThermometerSensor::readObjectTempC(void)
{
   if(_WeIRThermometerSensor.reset()!=0)
  	return -200;
  _WeIRThermometerSensor.write_byte(0x03);
  _WeIRThermometerSensor.respond();
  _Sensor1=_WeIRThermometerSensor.read_byte();
  _Sensor2=_WeIRThermometerSensor.read_byte();	
  _data=((uint16_t)_Sensor2 << 8 | _Sensor1)*0.02-273.15;
  return _data;
}




