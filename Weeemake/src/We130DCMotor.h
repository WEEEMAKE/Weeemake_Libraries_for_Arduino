#ifndef _We130DCMotor_H
#define _We130DCMotor_H

#include "WePort.h"

class We130DCMotor
{
public:

  We130DCMotor(uint8_t port=0); 
  void reset(uint8_t port=0);

  void run(int16_t speed);
  void stop(void);
  void runTo(int16_t speed);

  
private:
	WeOneWire _130DCMotor;
	//volatile uint8_t dc_dir_pin;
  //  volatile uint8_t dc_pwm_pin;
    int16_t  last_speed=0;
  //  uint8_t  onBoard_flag=0;
	//uint8_t  motor_flag=0;
};

#endif

