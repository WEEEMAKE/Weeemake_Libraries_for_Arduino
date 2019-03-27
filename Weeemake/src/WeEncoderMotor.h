#ifndef _WeEncoderMotor_H
#define _WeEncoderMotor_H

#include "WePort.h"

class WeEncoderMotor
{
public:

  WeEncoderMotor(uint8_t port=0); 
  void reset(uint8_t port=0);
  void run(int16_t speed);
  void stop(void);
  long getCurrentPosition(void);
  void setPositionOrigin(void);
  void moveTo(uint8_t speed,long position);
  void move(uint8_t speed,long position);
  void runSpeed(int16_t speed);
  void setAccurary(uint8_t num);
  
private:
	WeOneWire _EncoderMotor;
	volatile uint8_t dc_dir_pin;
    volatile uint8_t dc_pwm_pin;
    int16_t  last_speed=0;
	uint8_t  motor_flag=0;
	long count_pulse=0;
};

#endif

