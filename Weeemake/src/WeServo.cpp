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
    int pulsewidth = (angle * 10) + 600; //���Ƕ�ת��Ϊ500-2480������ֵ
    if(_IRflag==1) pulsewidth = (angle * 8) + 400;		
    digitalWrite(_Servopin, HIGH);   //������ӿڵ�ƽ����
    delayMicroseconds(pulsewidth);  //��ʱ����ֵ��΢����
    digitalWrite(_Servopin, LOW);    //������ӿڵ�ƽ����
    delayMicroseconds(20000 - pulsewidth);
  }
  delay(100);
}


