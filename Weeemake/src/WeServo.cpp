#include "WeServo.h"


WeServo::WeServo(uint8_t port,bool IRflag)
{
  _Servopin=port;
  pinMode(_Servopin, OUTPUT);
  _IRflag=IRflag;
}
void WeServo::reset(uint8_t port,bool IRflag)
{
  _Servopin=port;
  pinMode(_Servopin, OUTPUT);
  _IRflag=IRflag;
}


void WeServo::write(uint8_t angle)
{
 if(angle>180) angle=180;
 for(int i=0;i<50;i++){
    int pulsewidth = (angle * 10) + 600; //将角度转化为500-2480的脉宽值
    if(_IRflag==1) pulsewidth = (angle * 8) + 400;		
    digitalWrite(_Servopin, HIGH);   //将舵机接口电平至高
    delayMicroseconds(pulsewidth);  //延时脉宽值的微秒数
    digitalWrite(_Servopin, LOW);    //将舵机接口电平至低
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(100);
}


