#ifndef _WeDCMotor_S_H
#define _WeDCMotor_S_H

#include "WePort.h"

class WeDCMotor_S
{
public:
  
  WeDCMotor_S(uint8_t port=0); 
  void reset(uint8_t port=0);
  void run(int16_t speed);
  void move(uint8_t direction, int16_t speed);
  void stop(void);

  
private:
	volatile uint8_t dc_dir_pin;
    volatile uint8_t dc_pwm_pin;
    int16_t  last_speed=0;
    uint8_t  onBoard_flag=0;
	uint8_t  motor_flag=0;
	uint8_t  setPWM_flag=0;
};

#endif

