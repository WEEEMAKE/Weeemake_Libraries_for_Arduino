#include "WeInfraredSender.h"

WeInfraredSender::WeInfraredSender(uint8_t port)
{
	_Sensorpin = port;
	pinMode(_Sensorpin,OUTPUT);
}

void WeInfraredSender::reset(uint8_t port)
{
	_Sensorpin = port;
	pinMode(_Sensorpin,OUTPUT);
}

void WeInfraredSender::generate_38kHzPlus(uint16_t x, bool y)
{
	for(uint16_t i=0;i<x;i++)//15=386US
	{ 
		if(y){
			digitalWrite(_Sensorpin,1);
			delayMicroseconds(9);
			digitalWrite(_Sensorpin,0);
			delayMicroseconds(9);
		}
		else{
			digitalWrite(_Sensorpin,0);
			delayMicroseconds(20);
		}            
	}
}

void WeInfraredSender::send_code(uint8_t data_code)
{
    for(uint8_t i=0;i<8;i++){
		if((data_code&0x01)==0x01){
			generate_38kHzPlus(23,1);
			generate_38kHzPlus(64,0);             
		}
		else{
			generate_38kHzPlus(23,1);
			generate_38kHzPlus(21,0);  
		}
		data_code=data_code>>1;
	}  
}

void WeInfraredSender::send_nec_message(uint8_t user_code, uint8_t data_code)
{
	noInterrupts();
    uint8_t temp;
  
    temp = user_code;
     
    generate_38kHzPlus(310,1);//发送9ms的起始码
    generate_38kHzPlus(170,0);//发送4.5ms的结果码
     
    send_code(temp);//用户识别码
    temp=~temp;
    send_code(temp);//用户识别码反吗
    
    temp=data_code;
    send_code(temp);//操作码
    temp=~temp;
    send_code(temp);//操作码反码
     
    generate_38kHzPlus(21,1);//发送结束码
    interrupts();
}