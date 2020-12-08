#include "WeEncoderMotor.h"

WeEncoderMotor::WeEncoderMotor(uint8_t port)
{
   reset(port);
}


void WeEncoderMotor::reset(uint8_t port)
{
	_EncoderMotor.reset(port);
	motor_flag=1;
	last_speed=300;
}

void WeEncoderMotor::run(int16_t speed)
{ 
  
  speed	= speed > 255 ? 255 : speed;
  speed	= speed < -255 ? -255 : speed;

  if(last_speed != speed)
  {
    last_speed = speed;
  }
  else
  {
    return;
  }
  
  if(speed >= -2)
  {
     _EncoderMotor.reset();
	 _EncoderMotor.write_byte(0x02);
     _EncoderMotor.reset();
     _EncoderMotor.write_byte(motor_flag);
     _EncoderMotor.write_byte((uint8_t)(speed/2.55));
     delayMicroseconds(500);
  }
  else
  {
    
	  _EncoderMotor.reset();
	  _EncoderMotor.write_byte(0x02);
	  _EncoderMotor.reset();
      _EncoderMotor.write_byte(motor_flag);
      _EncoderMotor.write_byte((uint8_t)(100-speed/2.55));
      delayMicroseconds(500);
	
  }
}

long WeEncoderMotor:: getCurrentPosition(void)
{
	 _EncoderMotor.reset();
	 _EncoderMotor.write_byte(0x03);
	 _EncoderMotor.respond();
      count_pulse=_EncoderMotor.read_byte();
      count_pulse=(((long)_EncoderMotor.read_byte())<<8)+count_pulse;
	 count_pulse=(((long)_EncoderMotor.read_byte())<<16)+count_pulse;
	 count_pulse=(((long)_EncoderMotor.read_byte())<<24)+count_pulse;
	 return count_pulse;
}
void WeEncoderMotor:: setPositionOrigin(void)
{
	 _EncoderMotor.reset();
	 _EncoderMotor.write_byte(0x04);
}

void WeEncoderMotor:: stop(void)
{
	_EncoderMotor.reset();
	_EncoderMotor.write_byte(0x02);
     _EncoderMotor.reset();
     _EncoderMotor.write_byte(motor_flag);
     _EncoderMotor.write_byte(0);
	 last_speed = 300;
}
void WeEncoderMotor:: moveTo(uint8_t speed,long position)
{  
       _EncoderMotor.reset();
	  _EncoderMotor.write_byte(0x05);
	  _EncoderMotor.reset();
       _EncoderMotor.write_byte(speed/2.55);
       _EncoderMotor.write_byte((uint8_t)position);
	  _EncoderMotor.write_byte((uint8_t)(position>>8));
	  _EncoderMotor.write_byte((uint8_t)(position>>16));
	  _EncoderMotor.write_byte((uint8_t)(position>>24));
       delayMicroseconds(500);
      last_speed = 300;
}
void WeEncoderMotor:: move(uint8_t speed,long position)
{
	
       _EncoderMotor.reset();
	  _EncoderMotor.write_byte(0x06);
	  _EncoderMotor.reset();
       _EncoderMotor.write_byte(speed/2.55);
       _EncoderMotor.write_byte((uint8_t)position);
	  _EncoderMotor.write_byte((uint8_t)(position>>8));
	  _EncoderMotor.write_byte((uint8_t)(position>>16));
	  _EncoderMotor.write_byte((uint8_t)(position>>24));
       delayMicroseconds(500);
	   last_speed = 300;
}

void WeEncoderMotor:: runSpeed(int16_t speed)    //50ms脉冲数
{
     
	if(last_speed == speed)
	{
	    return;
	}
	
     if (speed==0)
     {
		run(0);
		return;
	}
	last_speed = speed;

	  _EncoderMotor.reset();
	  _EncoderMotor.write_byte(0x07);
	  _EncoderMotor.reset();
       _EncoderMotor.write_byte((uint8_t)speed);
	  _EncoderMotor.write_byte((uint8_t)(speed>>8));

}

void WeEncoderMotor:: runSpeed_188(int16_t speed)    //转/分  输出轴
{	
    speed=speed*49/100;   //45*13/60/20=0.49
    runSpeed(speed); 
}

void WeEncoderMotor::setAccurary(uint8_t num)   //>=1
{
	_EncoderMotor.reset();
	_EncoderMotor.write_byte(0x08);
	_EncoderMotor.reset();
	_EncoderMotor.write_byte(num);

}


