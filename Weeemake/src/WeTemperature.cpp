#include "WeTemperature.h"


WeTemperature::WeTemperature(uint8_t port)
{
  _DataPin=port;
  _ts.reset(port);
}

void WeTemperature::reset(uint8_t port)
{
  _ts.reset(port);
}

float WeTemperature::temperature(void)
{
  byte  i;
  byte  present = 0;
  byte  type_s;
  byte  data[12];
  byte	addr[8];
  float celsius;
  long  time;

  _ts.reset();
  _ts.skip();
  _ts.write(STARTCONVO);       // start conversion, with parasite power on at the end
  time = millis();
  while(!_ts.readIO() && (millis() - time) < 750)
  {
    ;
  }

  present = _ts.reset();
  _ts.skip();
  _ts.write(READSCRATCH);
  for(i = 0; i < 5; i++)      // we need 9 bytes
  {
    data[i] = _ts.read();
  }

  int16_t rawTemperature = (data[1] << 8) | data[0];

  return( (float)rawTemperature * 0.0625); // 12 bit
}




