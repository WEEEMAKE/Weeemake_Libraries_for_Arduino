
#ifndef _WeJoystick_H
#define _WeJoystick_H

#include "WePort.h"

class WeJoystick
{
public:

  WeJoystick(uint8_t port=0);
  void reset(uint8_t port=0);
  void readData(void);
  uint8_t showX(void);
  uint8_t showY(void);
  uint8_t showKey(void);
  uint8_t readValue(uint8_t axis);

  
private:
	WeOneWire _WeJoystick;
    volatile uint8_t  _Sensor1;
	volatile uint8_t  _Sensor2;
	volatile uint8_t  _Sensor3;
};

#endif

