#include "WeDCMotor_S.h"

void WeDCMotor_S::move(uint8_t direction, int16_t speed)
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

WeDCMotor_S::WeDCMotor_S(uint8_t port)
{
  reset(port);
}


void WeDCMotor_S::reset(uint8_t port)
{
  pinMode(WetwoPort[port].s2, OUTPUT);
  dc_pwm_pin=WetwoPort[port].s1;
  dc_dir_pin=WetwoPort[port].s2;
  onBoard_flag=1;

  last_speed=300;
}

void WeDCMotor_S::run(int16_t speed)
{ 
  if(setPWM_flag==0)
  {
     setfastPWM();
   setPWM_flag=1;
  }
  speed = speed > 255 ? 255 : speed;
  speed = speed < -255 ? -255 : speed;

  if(last_speed != speed)
  {
    last_speed = speed;
  }
  else
  {
    return;
  }
  if(speed >= 0){
    if(onBoard_flag==1){
      if(dc_dir_pin==7)  //ELF
      {
        digitalWrite(dc_dir_pin,HIGH);
        analogWrite(dc_pwm_pin, speed);
      }
      else if(dc_dir_pin==8)
      {
        digitalWrite(dc_dir_pin,HIGH);
        analogWrite(dc_pwm_pin, speed);
      }
    }
  }
  else{
    if(onBoard_flag==1){
     if(dc_dir_pin==7)
     {
         digitalWrite(dc_dir_pin,LOW);
         analogWrite(dc_pwm_pin, -speed);
      }
     if(dc_dir_pin==8)
     {
         digitalWrite(dc_dir_pin,LOW);
         analogWrite(dc_pwm_pin, -speed);
     }
   
    }
  }
}

void WeDCMotor_S:: stop(void)
{
  run(0);
}





