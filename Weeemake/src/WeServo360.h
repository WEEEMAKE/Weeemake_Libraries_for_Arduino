
#ifndef _WeServo360_H
#define _WeServo360_H

#include "WePort.h"

class WeServo360
{
public:

  WeServo360(uint8_t port=0);
  void reset(uint8_t port=0);
  void write(uint16_t angle);

 
private:
   uint8_t _Servopin;
   //bool _IRflag;
};

#endif

