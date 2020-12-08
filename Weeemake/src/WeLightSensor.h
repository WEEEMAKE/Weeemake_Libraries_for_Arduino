
#ifndef WeLightSensor_H
#define WeLightSensor_H

#include "WePort.h"

class WeLightSensor
{
public:
	WeLightSensor(uint8_t port=0);
	int16_t read(void);
  
private:
	uint8_t _Sensorpin;
};

class WeLightSensor_RJ
{
public:
  WeLightSensor_RJ(uint8_t port=0);
  void reset(uint8_t port=0);

  uint16_t read(void);

private:
	WeOneWire _WeLightSensor_RJ;
    //volatile uint8_t  _Sensor;
};

#endif

