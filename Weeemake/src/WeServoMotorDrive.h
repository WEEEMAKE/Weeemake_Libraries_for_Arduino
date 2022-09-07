
#ifndef _WeServoMotorDrive_H
#define _WeServoMotorDrive_H

#include "WePort.h"

class WeServoMotorDrive
{
public:

  WeServoMotorDrive(uint8_t port=0);
  void reset(uint8_t port=0);
  void write(uint8_t pin, uint8_t angle);
  void RGBshow(uint8_t pin, uint8_t index,uint8_t red, uint8_t green, uint8_t blue);

  
private:
   WeOneWire _WeServoMotorDrive;
   uint8_t s1,s2;
};

#endif

