#ifndef _WeEncoderMotor188_H
#define _WeEncoderMotor188_H

#include "WePort.h"
#include "WeEncoderMotor.h"

class WeEncoderMotor188 : public WeEncoderMotor
{
public:
  WeEncoderMotor188(uint8_t port=0);
  void runSpeed(int16_t speed);
};

#endif

