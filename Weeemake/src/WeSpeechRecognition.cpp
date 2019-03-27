#include "WeSpeechRecognition.h"


WeSpeechRecognition::WeSpeechRecognition(uint8_t port)
{
   reset(port);
}

void WeSpeechRecognition::reset(uint8_t port)
{
	_WeSpeechRecognition.reset(port);
}

//void WeSpeechRecognition::setKeyword(String str)
//{
//	setKeyword(str.c_str());
//}

void WeSpeechRecognition::setKeyword(const char *str)
{
	if(_WeSpeechRecognition.reset()!=0) return ;
    _WeSpeechRecognition.write_byte(0x02);
    if(_WeSpeechRecognition.reset()!=0) return ;
	_WeSpeechRecognition.write_byte(0x00);
	for(int i=0;i<DATA_A;i++)
	{
	   char v = str[i];
	   if(v ==0) break;
	   _WeSpeechRecognition.write_byte(v);	   
	}
	_WeSpeechRecognition.write_byte(0x00);	
	delay(10);
}

void WeSpeechRecognition::setPassword(int8_t num,const char *str)
{
	if(_WeSpeechRecognition.reset()!=0) return ;
    _WeSpeechRecognition.write_byte(0x02);
    if(_WeSpeechRecognition.reset()!=0) return ;
	_WeSpeechRecognition.write_byte(num);
	for(int i=0;i<DATA_A;i++)
	{
	   char v = str[i];
	   if(v ==0) break;
	   _WeSpeechRecognition.write_byte(v);	   
	}
	_WeSpeechRecognition.write_byte(0x00);	
	delay(10);
}

uint8_t WeSpeechRecognition::read(void)
{
	if(_WeSpeechRecognition.reset()!=0) 
		return 0 ;
    _WeSpeechRecognition.write_byte(0x03);
   _WeSpeechRecognition.respond();
   uint8_t value=_WeSpeechRecognition.read_byte();
   delay(50);
   return value;
}

void WeSpeechRecognition::setTriggerMode(uint8_t mode)
{
	if(_WeSpeechRecognition.reset()!=0) 
		return  ;
   _WeSpeechRecognition.write_byte(0x04);
    if(_WeSpeechRecognition.reset()!=0) return ;
	_WeSpeechRecognition.write_byte(mode-1);
    delay(10);
}

void WeSpeechRecognition::setResponseRate(uint8_t rate)
{
	if(_WeSpeechRecognition.reset()!=0) 
		return  ;
   _WeSpeechRecognition.write_byte(0x05);
    if(_WeSpeechRecognition.reset()!=0) return ;
	_WeSpeechRecognition.write_byte(rate);
   delay(10);
}

void WeSpeechRecognition::beginTrigger(void)  //trigger mode
{
	if(_WeSpeechRecognition.reset()!=0) 
		return  ;
   _WeSpeechRecognition.write_byte(0x06); 
   delay(10);
}
void WeSpeechRecognition::stopTrigger(void)  //trigger mode
{
	if(_WeSpeechRecognition.reset()!=0) 
		return  ;
   _WeSpeechRecognition.write_byte(0x07); 
   delay(10);
}


