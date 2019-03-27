
#ifndef WeButton_H
#define WeButton_H

#include "WePort.h"

class WeButton
{
public:

  WeButton(uint8_t port=0);

  int16_t read(void);
  
 private:
	uint8_t _Sensorpin;

};

#endif

