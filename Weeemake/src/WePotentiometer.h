
#ifndef _WePotentiometer_H
#define _WePotentiometer_H

#include "WePort.h"

class WePotentiometer
{
public:

  WePotentiometer(uint8_t port=0);
  void reset(uint8_t port=0);
  void CloseLED(void);
  void OpenLED(void);
  uint8_t readAnalog(void);

  
private:
	WeOneWire _WePotentiometer;
    volatile uint8_t  _Sensor1;
};

#endif

