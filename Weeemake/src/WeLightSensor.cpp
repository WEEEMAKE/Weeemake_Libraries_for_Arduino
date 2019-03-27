#include "WeLightSensor.h"

WeLightSensor::WeLightSensor(uint8_t port)
{
  _Sensorpin=port;
}



int16_t WeLightSensor::read(void)
{
   return(analogRead(_Sensorpin));
}





