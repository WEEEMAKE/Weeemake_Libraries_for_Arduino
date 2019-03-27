#include "We4LEDButton.h"


We4LEDButton::We4LEDButton(uint8_t port)
{
  reset(port);
}
void We4LEDButton::reset(uint8_t port)
{
	_We4LEDButton.reset(port);
}

void We4LEDButton::openLED(uint8_t value)
{
    switch(value)
    {
      case 1: value=1;break;
	  case 2: value=2;break;
	  case 3: value=4;break;
	  case 4: value=8;break;
	  default: break;
    }
	if(_We4LEDButton.reset()!=0)
       return ;
    _We4LEDButton.write_byte(0x03);
    if(_We4LEDButton.reset()!=0)
       return ;
	_We4LEDButton.write_byte(value);

}
void We4LEDButton::closeLED(uint8_t value)
{
    switch(value)
    {
      case 1: value=1;break;
	  case 2: value=2;break;
	  case 3: value=4;break;
	  case 4: value=8;break;
	  default: break;
    }
	if(_We4LEDButton.reset()!=0)
       return ;
    _We4LEDButton.write_byte(0x04);
    if(_We4LEDButton.reset()!=0)
       return ;
	_We4LEDButton.write_byte(value);
 
}

void We4LEDButton::setLed(uint8_t index, bool isOn)
{
  if(_We4LEDButton.reset())return;
  _We4LEDButton.write_byte(isOn ? 3 : 4);
  if(_We4LEDButton.reset())return;
  uint8_t value = index ? (1 << (index - 1)) : 0xF;
  _We4LEDButton.write_byte(value);
}

uint8_t We4LEDButton::readValue(void)
{
  if(_We4LEDButton.reset()!=0)
    return 0;
  _We4LEDButton.write_byte(0x02);
  _We4LEDButton.respond();
  _Sensor1=_We4LEDButton.read_byte();
  return _Sensor1;
}


uint8_t We4LEDButton::readKey(void)
{
  if(_We4LEDButton.reset()!=0)
    return 0;
  _We4LEDButton.write_byte(0x02);
  _We4LEDButton.respond();
  _Sensor1=_We4LEDButton.read_byte();
  switch(_Sensor1)
    {
      case 1: _Sensor1=1;break;
	  case 2: _Sensor1=2;break;
	  case 4: _Sensor1=3;break;
	  case 8: _Sensor1=4;break;
	  default: break;
    }
  return _Sensor1;
}



