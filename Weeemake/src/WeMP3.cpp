#include "WeMP3.h"


WeMP3::WeMP3(uint8_t port)
{
   _WeMP3.reset(port);
}
void WeMP3::reset(uint8_t port)
{
	_WeMP3.reset(port);
}

void WeMP3::appointMusic(uint16_t num)
{
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x02);
    if(_WeMP3.reset()!=0)
       return ;
	_WeMP3.write_byte((uint8_t)(num>>8));
	_WeMP3.write_byte((uint8_t)num);
	delay(60);
}

void WeMP3::appointVolume(uint8_t num)
{
     if(num>22)
		num=22;
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x03);
    if(_WeMP3.reset()!=0)
       return ;
	_WeMP3.write_byte(num);
	delay(60);
}

void WeMP3::nextMusic(void)
{
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x04);
	delay(60);
}
void WeMP3::pause(void)
{
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x05);
	delay(60);
}
void WeMP3::play(void)
{
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x06);
	delay(60);
}
void WeMP3::appointDevice(uint8_t devtype)
{
    if((devtype!=0x02)&&(devtype!=0x04))
		return;
	if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x07);
    if(_WeMP3.reset()!=0)
       return ;
	_WeMP3.write_byte(devtype);
	delay(210);
}
uint8_t WeMP3::isOver(void)
{
	if(_WeMP3.reset()!=0)
       return 2;
    _WeMP3.write_byte(0x08);
    _WeMP3.respond();
    _data1=_WeMP3.read_byte();

   return _data1;
}
void WeMP3::prevMusic(void)
{
   if(_WeMP3.reset()!=0)
       return ;
    _WeMP3.write_byte(0x09);
    delay(60);
}


