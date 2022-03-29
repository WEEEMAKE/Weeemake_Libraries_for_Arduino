
#ifndef WeIRThermometerSensor_H
#define WeIRThermometerSensor_H

#include "WePort.h"

class WeIRThermometerSensor
{
public:

  WeIRThermometerSensor(uint8_t port=0);
  void reset(uint8_t port=0);

  float readAmbientTempC(void);
  float readObjectTempC(void);


  
private:
	WeOneWire _WeIRThermometerSensor;
    volatile uint8_t  _Sensor1;
    volatile uint8_t  _Sensor2;
	volatile float  _data;
};

#endif

