#include "WeDCMotor.h"

void WeDCMotor::move(uint8_t direction, int16_t speed)
{
  //1,2,3,4 => F,B,L,R
  reset(2);
  if(direction == 1 || direction == 4){
    run(-speed);
  }else{
    run(speed);
  }
  reset(1);
  if(direction == 1 || direction == 3){
    run(speed);
  }else{
    run(-speed);
  }
}

WeDCMotor::WeDCMotor(uint8_t port)
{
  reset(port);
}


void WeDCMotor::reset(uint8_t port)
{
  if(port > 2)
  {
    _DCMotor.reset(WetwoPort[port].s1);
    motor_flag=WetwoPort[port].s2;
    onBoard_flag=0;
  }else{
    pinMode(WetwoPort[port].s2, OUTPUT);
    dc_pwm_pin=WetwoPort[port].s1;
    dc_dir_pin=WetwoPort[port].s2;
    onBoard_flag=1;
  }
  last_speed=300;
}

void WeDCMotor::run(int16_t speed)
{ 
  if(setPWM_flag==0)
  {
     setfastPWM();
	 setPWM_flag=1;
  }
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
  if(speed >= 0)
  {
   if(onBoard_flag==1)
   {

	 if(dc_dir_pin==7)  //ELF
	 {
       digitalWrite(dc_dir_pin,LOW);
       analogWrite(dc_pwm_pin, speed);
	  }
	 else if(dc_dir_pin==8)
	 {
       digitalWrite(dc_dir_pin,HIGH);
       analogWrite(dc_pwm_pin, speed);
	 }
	 
	 else if(dc_dir_pin==9) //ELF MINI
	 {
       digitalWrite(dc_dir_pin,HIGH);
       analogWrite(dc_pwm_pin, 255-speed);
	  }
	 else if(dc_dir_pin==6)
	 {
       digitalWrite(dc_dir_pin,HIGH);
       analogWrite(dc_pwm_pin, 255-speed);
	 }

   }
   else
   {
     _DCMotor.reset();
	 _DCMotor.write_byte(0x02);
     _DCMotor.reset();
     _DCMotor.write_byte(motor_flag);
     _DCMotor.write_byte((uint8_t)(speed/2.55));
     delayMicroseconds(500);
   }
  }
  else
  {
    if(onBoard_flag==1)
    {
     if(dc_dir_pin==7)
	 {
       digitalWrite(dc_dir_pin,HIGH);
       analogWrite(dc_pwm_pin, -speed);
	  }
	 if(dc_dir_pin==8)
	 {
       digitalWrite(dc_dir_pin,LOW);
       analogWrite(dc_pwm_pin, -speed);
	 }
	 
	 if(dc_dir_pin==9) //ELF MINI
     {
		digitalWrite(dc_pwm_pin,HIGH);
		analogWrite(dc_dir_pin, 255+speed);
	 }
	 if(dc_dir_pin==6)
	 {
		digitalWrite(dc_pwm_pin,HIGH);
		analogWrite(dc_dir_pin, 255+speed);
	 }
    }
	else
	{
	  _DCMotor.reset();
	  _DCMotor.write_byte(0x02);
	  _DCMotor.reset();
      _DCMotor.write_byte(motor_flag);
      _DCMotor.write_byte((uint8_t)(100-speed/2.55));
      delayMicroseconds(500);
	}
  }
}

void WeDCMotor:: stop(void)
{
	run(0);
}





