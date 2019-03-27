#include "WeEncoderMotor188.h"

WeEncoderMotor188::WeEncoderMotor188(uint8_t port)
{
   reset(port);
}

void WeEncoderMotor188::runSpeed(int16_t speed)
{	
    WeEncoderMotor::runSpeed(speed*49/100);
}