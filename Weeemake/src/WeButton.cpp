#include "WeButton.h"


WeButton::WeButton(uint8_t port)
{
  _Sensorpin=port;
}

int16_t WeButton::read(void)
{
   pinMode(_Sensorpin, INPUT);
   return(digitalRead(_Sensorpin));
}





