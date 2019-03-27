#include "WeRGBLED_RJ.h"

WeRGBLED_RJ::WeRGBLED_RJ(uint8_t port)
{
  _WeRGBLED_RJ.reset(port);
}
void WeRGBLED_RJ::reset(uint8_t port)
{
  _WeRGBLED_RJ.reset(port);
}


void WeRGBLED_RJ::setColor(uint8_t index,uint8_t red, uint8_t green, uint8_t blue)
{
	if(index == 0){
		for(int i=0; i<5; ++i){
			index = i * 3;
			_5RGB_data[index] = green;
			_5RGB_data[index + 1] = red;
			_5RGB_data[index + 2] = blue;
		}
	}else if(index <= 5){
		index = (index - 1) * 3;
		_5RGB_data[index] = green;
		_5RGB_data[index + 1] = red;
		_5RGB_data[index + 2] = blue;
	}
}
void WeRGBLED_RJ::show()
{
  RGBShow();
}
void WeRGBLED_RJ::RGBShow(void)
{
   if (_WeRGBLED_RJ.reset()!=0)
   	return;
  _WeRGBLED_RJ.write_byte(0x02);
  if (_WeRGBLED_RJ.reset()!=0)
   	return;
  for(int i=0;i<15;i++)
  {
     _WeRGBLED_RJ.write_byte(_5RGB_data[i]); 
  }
}

void WeRGBLED_RJ::setColor_j(uint8_t index,uint8_t red, uint8_t green, uint8_t blue)
{
	if (_WeRGBLED_RJ.reset()!=0)
   	return;
	_WeRGBLED_RJ.write_byte(0x03);
	if (_WeRGBLED_RJ.reset()!=0)
   	return;

    _WeRGBLED_RJ.write_byte(index); 
	_WeRGBLED_RJ.write_byte(red); 
	_WeRGBLED_RJ.write_byte(green); 
	_WeRGBLED_RJ.write_byte(blue); 
}





