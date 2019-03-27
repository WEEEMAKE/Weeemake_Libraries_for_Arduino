
#ifndef _WeFlameSensor_H
#define _WeFlameSensor_H

#include "WePort.h"

class WeFlameSensor
{
public:

  WeFlameSensor(uint8_t port=0);
  void reset(uint8_t port=0);
  void readData(void);
  uint8_t showSensor1(void);
  uint8_t showSensor2(void);
  uint8_t showSensor3(void);
  uint8_t readValue(uint8_t index);


  
private:
	WeOneWire _WeFlameSensor;
    volatile uint8_t  _Sensor1,_Sensor2,_Sensor3;
};

#endif

