#include "WeFlameSensor.h"


WeFlameSensor::WeFlameSensor(uint8_t port)
{
  _WeFlameSensor.reset(port);
}
void WeFlameSensor::reset(uint8_t port)
{
	_WeFlameSensor.reset(port);
}


void WeFlameSensor::readData(void)
{
  if(_WeFlameSensor.reset()!=0)
    return ;
  _WeFlameSensor.write_byte(0x02);
  _WeFlameSensor.respond();
  _Sensor1=_WeFlameSensor.read_byte();
  _Sensor2=_WeFlameSensor.read_byte();
  _Sensor3=_WeFlameSensor.read_byte();

}
uint8_t WeFlameSensor::showSensor1(void)
{
   return _Sensor1;
}
uint8_t WeFlameSensor::showSensor2(void)
{
   return _Sensor2;
}

uint8_t WeFlameSensor::showSensor3(void)
{
   return _Sensor3;
}

uint8_t WeFlameSensor::readValue(uint8_t index)
{
  readData();
  switch(index){
    case 1: return _Sensor1;
    case 3: return _Sensor3;
  }
  return _Sensor2;
}





