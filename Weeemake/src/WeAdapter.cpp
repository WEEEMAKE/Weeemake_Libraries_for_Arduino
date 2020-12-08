#include "WeAdapter.h"


WeAdapter::WeAdapter(uint8_t port)
{
  _WeAdapter.reset(port);
}
void WeAdapter::reset(uint8_t port)
{
  _WeAdapter.reset(port);
}

void WeAdapter::write(uint8_t pin, uint8_t angle)
{
    if(_WeAdapter.reset()!=0)
       return ;
    _WeAdapter.write_byte(0x02);
    if(_WeAdapter.reset()!=0)
       return ;
	_WeAdapter.write_byte(pin);
	_WeAdapter.write_byte(angle);

}
void WeAdapter::RGBshow(uint8_t pin, uint8_t index,uint8_t red, uint8_t green, uint8_t blue)
{
	if(_WeAdapter.reset()!=0)
       return ;
    _WeAdapter.write_byte(0x03);
    if(_WeAdapter.reset()!=0)
       return ;
	_WeAdapter.write_byte(pin);
	_WeAdapter.write_byte(index);
	_WeAdapter.write_byte(red);
	_WeAdapter.write_byte(green);
	_WeAdapter.write_byte(blue);
	delayMicroseconds(2000);
}
void WeAdapter::RGBshow(uint8_t pin, uint8_t index,uint32_t color)
{
	RGBshow(pin, index, (color >> 16) & 0xFF, (color >> 8) & 0xFF, color & 0xFF);
}
float WeAdapter::readTemperature(uint8_t pin)
{
    if(pin>4) return 0;
	if(_WeAdapter.reset()!=0)
       return 0;
    _WeAdapter.write_byte(0x04+pin-1);
    _WeAdapter.respond();
	s1=_WeAdapter.read_byte();
	s2=_WeAdapter.read_byte();
	temperature   = (uint16_t)s2 << 8 | s1;
	temperature = temperature/100.0;
	return temperature;
}
uint8_t WeAdapter::analogRead(uint8_t pin)
{
	if(pin>4) return 0;
	if(_WeAdapter.reset()!=0)
		   return 0;
	_WeAdapter.write_byte(0x08+pin-1);
	_WeAdapter.respond();
	s1=_WeAdapter.read_byte();
	s2=_WeAdapter.read_byte();  //12bit ADC
	return s1;

}

void WeAdapter::digitalWrite(uint8_t pin,uint8_t val)
{
	if(val == LOW)
		s1=0;
	else
		s1=1;
	if(_WeAdapter.reset()!=0)
       return ;
    _WeAdapter.write_byte(0x0c);
    if(_WeAdapter.reset()!=0)
       return ;
	_WeAdapter.write_byte(pin);
	_WeAdapter.write_byte(s1);	
}

bool WeAdapter::digitalRead(uint8_t pin)
{
    if(pin>4) return 0;
	if(_WeAdapter.reset()!=0)
		   return 0;
	_WeAdapter.write_byte(0x0d+pin-1);
	_WeAdapter.respond();
	s1=_WeAdapter.read_byte();
	return s1;
}



