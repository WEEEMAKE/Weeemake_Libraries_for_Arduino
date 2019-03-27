#include "WeHumiture.h"


WeHumiture::WeHumiture(uint8_t port)
{
  _WeHumiture.reset(port);
}
void WeHumiture::reset(uint8_t port)
{
	_WeHumiture.reset(port);
}

void WeHumiture::startRead(void)
{
  if(_WeHumiture.reset()!=0)
  	return;
  _WeHumiture.write_byte(0x02);
  _WeHumiture.respond();
  _humidity=_WeHumiture.read_byte();
  _temperature=_WeHumiture.read_byte();
}

uint16_t WeHumiture::getHumidity(bool update)
{
  if(update)startRead();
  return (_humidity);
}
uint16_t WeHumiture::getTemperature(bool update)
{
  if(update)startRead();
  return (_temperature);
}

uint16_t WeHumiture::getValue(uint8_t type, bool update)
{
  if(update)startRead();
  if(type == 0)return _temperature;
  if(type == 1)return _humidity;
  return 0;
}


