#include "We36EncoderMotor.h"

We36EncoderMotor::We36EncoderMotor(uint8_t port,uint8_t flag)
{
   reset(port,flag);
}


void We36EncoderMotor::reset(uint8_t port,uint8_t flag)
{
	_36EncoderMotor.reset(port);
	motor_flag=flag;
	last_speed=300;
}

void We36EncoderMotor::run(int16_t speed)
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
     _36EncoderMotor.reset();
	 _36EncoderMotor.write_byte(0x02);
     _36EncoderMotor.reset();
     _36EncoderMotor.write_byte(motor_flag);
     _36EncoderMotor.write_byte((uint8_t)(speed/2.55));
     delayMicroseconds(500);
  }
  else
  {
    
	  _36EncoderMotor.reset();
	  _36EncoderMotor.write_byte(0x02);
	  _36EncoderMotor.reset();
      _36EncoderMotor.write_byte(motor_flag);
      _36EncoderMotor.write_byte((uint8_t)(100-speed/2.55));
      delayMicroseconds(500);
	
  }
}

long We36EncoderMotor:: getCurrentPosition(void)
{
	 _36EncoderMotor.reset();
	 if(motor_flag==1)
	 	_36EncoderMotor.write_byte(0x03);
	 else if(motor_flag==2)
	 	_36EncoderMotor.write_byte(0x09);
	 _36EncoderMotor.respond();
      count_pulse=_36EncoderMotor.read_byte();
      count_pulse=(((long)_36EncoderMotor.read_byte())<<8)+count_pulse;
	 count_pulse=(((long)_36EncoderMotor.read_byte())<<16)+count_pulse;
	 count_pulse=(((long)_36EncoderMotor.read_byte())<<24)+count_pulse;
	 return count_pulse;
}
void We36EncoderMotor:: setPositionOrigin(void)
{
	 _36EncoderMotor.reset();
	 if(motor_flag==1)
	 	_36EncoderMotor.write_byte(0x04);
	 else if(motor_flag==2)
	 	_36EncoderMotor.write_byte(0x0A);
}

void We36EncoderMotor:: stop(void)
{
	_36EncoderMotor.reset();
	_36EncoderMotor.write_byte(0x02);
     _36EncoderMotor.reset();
     _36EncoderMotor.write_byte(motor_flag);
     _36EncoderMotor.write_byte(0);
	 last_speed = 300;
}
void We36EncoderMotor:: moveTo(uint8_t speed,long position)
{  
       _36EncoderMotor.reset();
	  if(motor_flag==1) 
	  	_36EncoderMotor.write_byte(0x05);
	  else if(motor_flag==2)
	  	_36EncoderMotor.write_byte(0x0B);
	  _36EncoderMotor.reset();
       _36EncoderMotor.write_byte(speed/2.55);
       _36EncoderMotor.write_byte((uint8_t)position);
	  _36EncoderMotor.write_byte((uint8_t)(position>>8));
	  _36EncoderMotor.write_byte((uint8_t)(position>>16));
	  _36EncoderMotor.write_byte((uint8_t)(position>>24));
       delayMicroseconds(500);
      last_speed = 300;
}
void We36EncoderMotor:: move(uint8_t speed,long position)
{
	
       _36EncoderMotor.reset();
	   if(motor_flag==1) 
	  		_36EncoderMotor.write_byte(0x06);
	   else if(motor_flag==2)
	   		_36EncoderMotor.write_byte(0x0C);
	  _36EncoderMotor.reset();
       _36EncoderMotor.write_byte(speed/2.55);
       _36EncoderMotor.write_byte((uint8_t)position);
	  _36EncoderMotor.write_byte((uint8_t)(position>>8));
	  _36EncoderMotor.write_byte((uint8_t)(position>>16));
	  _36EncoderMotor.write_byte((uint8_t)(position>>24));
       delayMicroseconds(500);
	   last_speed = 300;
}

void We36EncoderMotor:: runSpeed(int16_t speed)    //100msÂö³åÊý
{

	speed=speed/2; 
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

	  _36EncoderMotor.reset();
	  if(motor_flag==1)
	  	_36EncoderMotor.write_byte(0x07);
	  else if(motor_flag==2)
	  	_36EncoderMotor.write_byte(0x0D);
	  _36EncoderMotor.reset();
       _36EncoderMotor.write_byte((uint8_t)speed);
	  _36EncoderMotor.write_byte((uint8_t)(speed>>8));

}

void We36EncoderMotor::setAccurary(uint8_t num)   //>=1
{
	_36EncoderMotor.reset();
	_36EncoderMotor.write_byte(0x08);
	_36EncoderMotor.reset();
	_36EncoderMotor.write_byte(num);

}


