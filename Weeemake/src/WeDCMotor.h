#ifndef _WeDCMotor_H
#define _WeDCMotor_H

#include "WePort.h"

class WeDCMotor
{
public:
  
  WeDCMotor(uint8_t port=0); 
  void reset(uint8_t port=0);
  void run(int16_t speed);
  void move(uint8_t direction, int16_t speed);
  void stop(void);

  
private:
	WeOneWire _DCMotor;
	volatile uint8_t dc_dir_pin;
    volatile uint8_t dc_pwm_pin;
    int16_t  last_speed=0;
    uint8_t  onBoard_flag=0;
	uint8_t  motor_flag=0;
	uint8_t  setPWM_flag=0;
};

#endif

