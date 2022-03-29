#ifndef _We36EncoderMotor_H
#define _We36EncoderMotor_H

#include "WePort.h"

class We36EncoderMotor
{
public:

  We36EncoderMotor(uint8_t port,uint8_t flag); 
  void reset(uint8_t port,uint8_t flag);
  void run(int16_t speed);
  void stop(void);
  long getCurrentPosition(void);
  void setPositionOrigin(void);
  void moveTo(uint8_t speed,long position);
  void move(uint8_t speed,long position);
  void runSpeed(int16_t speed);
  void setAccurary(uint8_t num);
  
private:
	WeOneWire _36EncoderMotor;
    int16_t  last_speed=0;
	uint8_t  motor_flag=0;
	long count_pulse=0;
};

#endif

