
#ifndef _WeServo_H
#define _WeServo_H

#include "WePort.h"

class WeServo
{
public:

  WeServo(uint8_t port=0);
  void reset(uint8_t port=0);
  void write(uint8_t angle);

 
private:
   uint8_t _Servopin;
   //bool _IRflag;

};

#endif

